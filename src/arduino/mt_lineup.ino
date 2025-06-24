#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Keypad.h>

// WiFi credentials
const char* ssid = "cadalig-2.4G"; // Insert SSID
const char* password = "acidscrambler"; // Insert password

// API details
const String API_URL = "https://iudvswvunbniioryvyvs.supabase.co";
const String API_KEY = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Iml1ZHZzd3Z1bmJuaWlvcnl2eXZzIiwicm9sZSI6ImFub24iLCJpYXQiOjE3MjkzNDYxNDUsImV4cCI6MjA0NDkyMjE0NX0.j_SM_LXoWQEwasWP-xYrTyhyFzSQ7X7h7S_Cq6ysYI4";
const String TABLE_NAME = "tickets";

// Pin definitions for buttons
#define BUTTON_PIN 4
#define BUTTON_PIN2 13
#define BUTTON_PIN3 14

#define LED_PIN1 25
#define LED_PIN2 26
#define LED_PIN3 27

#define TX 3
#define RX 1

unsigned long debounceDuration = 50; // Debounce time in ms
unsigned long lastButtonTimes[3] = {0}; // Last time buttons were toggled
byte lastButtonStates[3] = {HIGH, HIGH, HIGH}; // Previous states for buttons

int currentIndex = 0;

// LCD settings
hd44780_I2Cexp lcd(0x27);
const int LCD_COLS = 20;
const int LCD_ROWS = 4;

const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;

char hexaKeys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[KEYPAD_ROWS] = {0, 2, 5, 15};
byte colPins[KEYPAD_COLS] = {16, 17, 18, 19};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

// Enumerations for menu options
enum MenuOption {
  LICENSING,
  REGISTRATION,
  LETAS,
  REFERENCE,
  MENU_COUNT // Total number of menu options
};

const char* licensingOptions[] = {
    "Student-Driver's Permit",
    "New Driver's License (Non-Professional)",
    "Conductor's License"
};

const char* registrationOptions[] = {
    "Sales Reporting and Registration of Motor Vehicles",
    "Vehicle Encoding/Linking",
    "Renewal of Motor Vehicle (MV) Registration"
};

const char* letasOptions[] = {
    "Settlement of Apprehension Cases",
    "LETAS Fines and Penalties",
    "Encoding of Alarm on Driver's License and Motor Vehicles in Relation to Orders Issued by Competent Courts or Quasi-Judicial Bodies"
};

// Function prototypes
void setupWiFi();
void displayMenu(int index);
void handleButtonPress(int buttonIndex);
int sendPostRequest(const String& transaction, int service_id, unsigned long long referenceNumber);
int sendGetRequest(const String& transaction, int service_id);

// LCD content functions
void displayLicensing(int index);
void displayRegistration(int index);
void displayLetas(int index);
void fetchTransactionByRef(const String& refNumber);
bool fetchReferenceData(const String& refNumber, String& transaction, int generalService, int& queueNumber);


// Setup function
void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, TX, RX);
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.clear();

  // Initialize buttons
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  pinMode(BUTTON_PIN3, INPUT_PULLUP);

  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  
  // WiFi setup
  setupWiFi();

  displayMenu(currentIndex);
}

// Main loop
void loop() {
  unsigned long currentTime = millis();

  // Check buttons
  byte buttonPins[] = {BUTTON_PIN, BUTTON_PIN2, BUTTON_PIN3};
  for (int i = 0; i < 3; i++) {
    if (currentTime - lastButtonTimes[i] > debounceDuration) {
      byte currentButtonState = digitalRead(buttonPins[i]);
      if (currentButtonState != lastButtonStates[i]) {
        lastButtonTimes[i] = currentTime;
        lastButtonStates[i] = currentButtonState;
        if (currentButtonState == HIGH) {
          handleButtonPress(i);
        }
      }
    }
  }
}

// Initialize WiFi connection
void setupWiFi() {
  WiFi.begin(ssid, password);
  digitalWrite(LED_PIN1, HIGH);
  Serial.print("Connecting to WiFi");
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    Serial.print(".");
    delay(500);
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected.");
    digitalWrite(LED_PIN1, LOW);
    digitalWrite(LED_PIN2, HIGH);
  } else {
    Serial.println("\nFailed to connect to WiFi.");
    digitalWrite(LED_PIN1, LOW);
  }
}

// Display menu on LCD
void displayMenu(int index) {
  lcd.clear();
  switch (index) {
    case LICENSING:
      lcd.print("[Licensing         ]");
      lcd.setCursor(0, 1);
      lcd.print(" Registration");
      lcd.setCursor(0, 2);
      lcd.print(" LETAS");
      lcd.setCursor(0, 3);
      lcd.print(" Print with Ref #   ");
      break;
    case REGISTRATION:
      lcd.print(" Licensing");
      lcd.setCursor(0, 1);
      lcd.print("[Registration      ]");
      lcd.setCursor(0, 2);
      lcd.print(" LETAS");
      lcd.setCursor(0, 3);
      lcd.print(" Print with Ref #   ");
      break;
    case LETAS:
      lcd.print(" Licensing");
      lcd.setCursor(0, 1);
      lcd.print(" Registration");
      lcd.setCursor(0, 2);
      lcd.print("[LETAS             ]");
      lcd.setCursor(0, 3);
      lcd.print(" Print with Ref #   ");
      break;
    case REFERENCE:
      lcd.print(" Licensing");
      lcd.setCursor(0, 1);
      lcd.print(" Registration");
      lcd.setCursor(0, 2);
      lcd.print(" LETAS");
      lcd.setCursor(0, 3);
      lcd.print("[Print with Ref #  ]");
  }
}

// Handle button press
// Global variable to track if in a submenu
bool inSubmenu = false; 
int submenuIndex = 0; // Tracks option in the current submenu

void handleSubmenu() {
    // Display the submenu based on the current selection
    switch (currentIndex) {
        case LICENSING:
            displayLicensing(submenuIndex);
            break;
        case REGISTRATION:
            displayRegistration(submenuIndex);
            break;
        case LETAS:
            displayLetas(submenuIndex);
            break;
        case REFERENCE:

            break;
    }
}



void handleButtonPress(int buttonIndex) {
    if (inSubmenu) {
        // Navigation within the submenu
        if (buttonIndex == 0) { // Next option
            submenuIndex = (submenuIndex + 1) % 4; // Assuming 3 options + Return
            handleSubmenu();
        } else if (buttonIndex == 1) { // Previous option
            submenuIndex = (submenuIndex - 1 + 4) % 4; // Wrap around options
            handleSubmenu();
        } else if (buttonIndex == 2) { // Select option
            if (submenuIndex == 3) { // Return is selected
                inSubmenu = false; // Exit submenu
                displayMenu(currentIndex); // Return to main menu
            } else {
                // Handle the selected submenu action
                const char* selectedOption = nullptr;

                switch (currentIndex) {
                    case LICENSING:
                        selectedOption = licensingOptions[submenuIndex];
                        break;
                    case REGISTRATION:
                        selectedOption = registrationOptions[submenuIndex];
                        break;
                    case LETAS:
                        selectedOption = letasOptions[submenuIndex];
                        break;
                }

                if (selectedOption) {
                    unsigned long long referenceNumber = esp_random() % 900000ULL + 100000ULL;
                    int count = sendPostRequest(selectedOption, currentIndex, referenceNumber); // Send selected option to the database
                    lcd.clear();
                    String queueNumber = "Queue no: " + String(count);
                    lcd.print(queueNumber);
                    lcd.setCursor(0, 1);
                    String refNumber = "Ref: " + String(referenceNumber);
                    lcd.print(refNumber);

                    Serial2.write("");
                    Serial2.write("");
                    Serial2.write("");

                    Serial2.write(0x1B); // ESC
                    Serial2.write('@');  // Initialize printer

                    // Set font to double height and double width (big font)
                    Serial2.write(0x1B); // ESC
                    Serial2.write('!');  // Select print mode
                    Serial2.write(0x30); // Double height and double width

                    // Print text in big font
                    Serial2.println(queueNumber);
                    Serial2.println(refNumber);

                    Serial2.write(0x1B);
                    Serial2.write('!');
                    Serial2.write(0x30);

                    Serial2.println(selectedOption);

                    delay(5000); // Pause for confirmation
                }

                // Redisplay submenu after action
                handleSubmenu();
            }
        }
    } else {
        // Navigation within the main menu
        if (buttonIndex == 0) { // Next menu
            currentIndex = (currentIndex + 1) % MENU_COUNT;
        } else if (buttonIndex == 1) { // Previous menu
            currentIndex = (currentIndex - 1 + MENU_COUNT) % MENU_COUNT;
        } else if (buttonIndex == 2) { // Enter submenu or reference number input
            if (currentIndex == REFERENCE) {
                lcd.clear();
                lcd.print("Enter Ref Number:");
                lcd.setCursor(0, 1);
                String inputReferenceNumber = ""; // Reset input

                char key;
                while (true) {
                    key = customKeypad.getKey();
                    if (key) {
                        if (key == '#') {
                            // Submit the entered reference number
                            lcd.clear();
                            String transaction;
                            int queueNumber;
                            bool success = fetchReferenceData(inputReferenceNumber, transaction, currentIndex, queueNumber);
                            if (success) {
                                lcd.print("Transaction:");
                                lcd.setCursor(0, 1);
                                lcd.print(transaction.substring(0, 20));
                                lcd.setCursor(0, 2);
                                lcd.print("Queue No: " + String(queueNumber));

                                Serial2.write(0x1B); // ESC
                                Serial2.write('@');  // Initialize printer

                                // Set font to double height and double width (big font)
                                Serial2.write(0x1B); // ESC
                                Serial2.write('!');  // Select print mode
                                Serial2.write(0x30); // Double height and double width


                                // Print text in big font
                                Serial2.println("");
                                Serial2.println("Queue No: " + String(queueNumber));
                                Serial2.println("Ref: " + inputReferenceNumber);

                                Serial2.write(0x1B);
                                Serial2.write('!');
                                Serial2.write(0x30);

                                Serial2.println(transaction);
                                Serial2.println("");
                                Serial2.println("");
                            } else {
                                lcd.print("Invalid Ref #");
                            }
                            delay(3000); // Show result for 3 seconds
                            break;
                        } else if (key == '*') {
                            // Cancel input and return to menu
                            displayMenu(currentIndex);
                            break;
                        } else {
                            inputReferenceNumber += key;
                            lcd.setCursor(0, 1);
                            lcd.print(inputReferenceNumber);
                        }
                    }
                }
            } else {
                inSubmenu = true;
                submenuIndex = 0; // Reset submenu index
                handleSubmenu();
            }
        }

        if (!inSubmenu) displayMenu(currentIndex);
    }
}



// Send HTTP POST request
int sendPostRequest(const String& transaction, int service_id, unsigned long long referenceNumber) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient https;

        digitalWrite(LED_PIN2, LOW);
        digitalWrite(LED_PIN3, HIGH);

        https.begin(API_URL + "/rest/v1/" + TABLE_NAME);
        https.addHeader("Content-Type", "application/json");
        https.addHeader("apikey", API_KEY);
        https.addHeader("Authorization", "Bearer " + API_KEY);

        String payload = "{";
        payload += "\"service_id\": " + String(transactionToId(transaction)) + ",";
        payload += "\"parent_service_id\": " + String(service_id + 1) + ",";
        payload += "\"ticket_number\": " + String(sendGetRequest(transaction, service_id) + 1) + ",";
        payload += "\"queue_time\": " + String(0) + ",";
        payload += "\"reference_number\": " + String(referenceNumber) + ",";
        payload += "\"status\": \"Pending\",";
        payload += "\"transaction\": \"" + transaction + ",";
        payload += "\"queue_time\": \"" + String(335) + "\"";
        payload += "}";

        int httpResponseCode = https.POST(payload);

        Serial.println(payload);

        if (httpResponseCode > 0) {
            Serial.println("POST successful: " + String(httpResponseCode));
            Serial.println("Sent data: " + transaction);
        } else {
            Serial.println("POST failed: " + String(httpResponseCode));
        }
        https.end();
        digitalWrite(LED_PIN2, HIGH);
        digitalWrite(LED_PIN3, LOW);
        return sendGetRequest(transaction, service_id);
    } else {
        Serial.println("WiFi not connected. POST failed.");
    }
}

int sendGetRequest(const String& transaction, int parent_service_id) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient https;

    https.begin(API_URL + "/rest/v1/" + TABLE_NAME + "?parent_service_id=eq." + String(parent_service_id + 1) + "&select=count");
    https.addHeader("apikey", API_KEY);
    https.addHeader("Authorization", "Bearer " + API_KEY);
    https.addHeader("Content-Type", "application/json");

    int httpResponseCode = https.GET();

    if (httpResponseCode > 0) {
      String payload = https.getString();
      Serial.println("HTTP Response: " + payload);
      Serial.println("HTTP Response Code: " + String(httpResponseCode));
      
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
          // Access the first element of the array
          int count = doc[0]["count"].as<int>(); // Correctly navigate into the array
          Serial.println("Count: " + String(count));
          return count;
      } else {
          Serial.println("Failed to parse JSON: " + String(error.c_str()));
          return 0; // Return a default value or handle the error
      }
      
    } else {
      Serial.println("Error: " + String(httpResponseCode));
    }

    https.end();
  } else {
    Serial.println("WiFi not connected.");
  }
}

// Display licensing options
void displayLicensing(int index) {
    switch (index) {
        case 0:
            lcd.clear();
            lcd.print("[Student-Driver's P]");
            lcd.setCursor(0, 1);
            lcd.print(" New Driver's Licen ");
            lcd.setCursor(0, 2);
            lcd.print(" Conductor's Licens ");
            lcd.setCursor(0, 3);
            lcd.print(" Return             ");
            break;
        case 1:
            lcd.clear();
            lcd.print(" Student-Driver's P ");
            lcd.setCursor(0, 1);
            lcd.print("[New Driver's Licen]");
            lcd.setCursor(0, 2);
            lcd.print(" Conductor's Licens ");
            lcd.setCursor(0, 3);
            lcd.print(" Return             ");
            break;
        case 2:
            lcd.clear();
            lcd.print(" Student-Driver's P ");
            lcd.setCursor(0, 1);
            lcd.print(" New Driver's Licen ");
            lcd.setCursor(0, 2);
            lcd.print("[Conductor's Licens]");
            lcd.setCursor(0, 3);
            lcd.print(" Return             ");
            break;
        case 3:
            lcd.clear();
            lcd.print(" Student-Driver's P ");
            lcd.setCursor(0, 1);
            lcd.print(" New Driver's Licen ");
            lcd.setCursor(0, 2);
            lcd.print(" Conductor's Licens ");
            lcd.setCursor(0, 3);
            lcd.print("[Return            ]");
            break;
    }
}

// Display registration options
void displayRegistration(int index) {
    switch (index) {
        case 0:
            lcd.clear();
            lcd.print("[Sales Reporting an]");
            lcd.setCursor(0, 1);
            lcd.print(" Vehicle Encoding/L ");
            lcd.setCursor(0, 2);
            lcd.print(" Renewal of Motor V ");
            lcd.setCursor(0, 3);
            lcd.print(" Return             ");
            break;
        case 1:
            lcd.clear();
            lcd.print(" Sales Reporting an ");
            lcd.setCursor(0, 1);
            lcd.print("[Vehicle Encoding/L]");
            lcd.setCursor(0, 2);
            lcd.print(" Renewal of Motor V ");
            lcd.setCursor(0, 3);
            lcd.print(" Return             ");
            break;
        case 2:
            lcd.clear();
            lcd.print(" Sales Reporting an ");
            lcd.setCursor(0, 1);
            lcd.print(" Vehicle Encoding/L ");
            lcd.setCursor(0, 2);
            lcd.print("[Renewal of Motor V]");
            lcd.setCursor(0, 3);
            lcd.print(" Return             ");
            break;
        case 3:
            lcd.clear();
            lcd.print(" Sales Reporting an ");
            lcd.setCursor(0, 1);
            lcd.print(" Vehicle Encoding/L ");
            lcd.setCursor(0, 2);
            lcd.print(" Renewal of Motor V ");
            lcd.setCursor(0, 3);
            lcd.print("[Return            ]");
            break;
    }
}

// Display LETAS options
void displayLetas(int index) {
    switch (index) {
        case 0:
            lcd.clear();
            lcd.print("[Settlement of Appr]");
            lcd.setCursor(0, 1);
            lcd.print(" LETAS Fines and Pe ");
            lcd.setCursor(0, 2);
            lcd.print(" Encoding of Alarm  ");
            lcd.setCursor(0, 3);
            lcd.print(" Return             ");
            break;
        case 1:
            lcd.clear();
            lcd.print(" Settlement of Appr ");
            lcd.setCursor(0, 1);
            lcd.print("[LETAS Fines and Pe]");
            lcd.setCursor(0, 2);
            lcd.print(" Encoding of Alarm  ");
            lcd.setCursor(0, 3);
            lcd.print(" Return             ");
            break;
        case 2:
            lcd.clear();
            lcd.print(" Settlement of Appr ");
            lcd.setCursor(0, 1);
            lcd.print(" LETAS Fines and Pe ");
            lcd.setCursor(0, 2);
            lcd.print("[Encoding of Alarm ]");
            lcd.setCursor(0, 3);
            lcd.print(" Return             ");
            break;
        case 3:
            lcd.clear();
            lcd.print(" Settlement of Appr ");
            lcd.setCursor(0, 1);
            lcd.print(" LETAS Fines and Pe ");
            lcd.setCursor(0, 2);
            lcd.print(" Encoding of Alarm  ");
            lcd.setCursor(0, 3);
            lcd.print("[Return            ]");
            break;
    }
}


bool fetchReferenceData(const String& refNumber, String& transaction, int generalService, int& queueNumber) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient https;

        // Modify the URL to fetch both transaction and ticket_number
        String url = API_URL + "/rest/v1/" + TABLE_NAME + 
                     "?reference_number=eq." + refNumber + 
                     "&select=transaction,ticket_number";
        
        https.begin(url);
        https.addHeader("apikey", API_KEY);
        https.addHeader("Authorization", "Bearer " + API_KEY);

        int httpResponseCode = https.GET();

        if (httpResponseCode > 0) {
            String payload = https.getString();
            Serial.println("HTTP Response: " + payload);

            // Parse the JSON response
            DynamicJsonDocument doc(1024);
            DeserializationError error = deserializeJson(doc, payload);

            if (!error) {
                // Assuming the response is an array of objects
                if (doc.size() > 0) {
                    transaction = doc[0]["transaction"].as<String>();
                    queueNumber = doc[0]["ticket_number"].as<int>();
                    
                    Serial.println("Fetched Transaction: " + transaction);
                    Serial.println("Fetched Queue Number: " + String(queueNumber));
                    
                    https.end();
                    return true;
                }
            } else {
                Serial.println("Failed to parse JSON: " + String(error.c_str()));
            }
        } else {
            Serial.println("Error: " + String(httpResponseCode));
        }

        https.end();
    } else {
        Serial.println("WiFi not connected.");
    }

    return false; // Return false if the operation fails
}

int transactionToId(String transaction) {
  if (transaction == "Student-Driver's Permit") {
    return 4;
  } else if (transaction == "New Driver's License (Non-Professional)") {
    return 5;
  } else if (transaction == "Conductor's License") {
    return 6;
  } else if (transaction == "Sales Reporting and Registration of Motor Vehicles") {
    return 7;
  } else if (transaction == "Vehicle Encoding/Linking") {
    return 8;
  } else if (transaction == "Renewal of Motor Vehicle (MV) Registration") {
    return 9;
  } else if (transaction == "Settlement of Apprehension Cases") {
    return 10;
  } else if (transaction == "LETAS Fines and Penalties") {
    return 11;
  } else if (transaction == "Encoding of Alarm on Driver's License and Motor Vehicles in Relation to Orders Issued by Competent Courts or Quasi-Judicial Bodies") {
    return 12;
  } else {
    // Return a default or error value if no match is found
    return -1; 
  }
}
