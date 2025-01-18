<template>
  <div class="scheduleBox">
    <navbar />
    <div class="globalHeader">
      <h1>Schedule</h1>
    </div>
    <div class="boxArea">
      <img
        class="prevButton"
        :src="previous"
        @click="goToPrevious"
        v-if="showPrevButton"
      />
      <div class="boxContainer" :style="containerStyle">
        <div
          v-for="(day, index) in twoWeeksDays"
          :key="index"
          class="card-group"
          :class="{ current: index === currentIndex, disabled: day.disabled }"
        >
          <div class="card mb-3" style="max-width: 53.625rem; height: 22.75rem">
            <div class="row g-0">
              <div class="col-md-6">
                <div
                  class="dateCardContent"
                  :class="{ 'disabled-card': !selectedServiceType }"
                >
                  <div class="dateTime">
                    <h3 class="card-title">
                      {{ day.formattedDay }}
                    </h3>
                    <h2 class="card-title">{{ day.formattedDate }}</h2>
                  </div>
                  <button
                    class="btn btn-primary specbtn"
                    :disabled="!day.selectedService"
                    @click="showQueueModal(day)"
                    style="
                      background-color: #052c65;
                      border: none;
                      width: 8.625rem;
                      height: 3.125rem;
                    "
                  >
                    Queue now
                  </button>
                </div>
                <span class="backToToday" @click="resetToToday"
                  >Back to today</span
                >
              </div>
              <div class="col-md-1">
                <div class="line"></div>
              </div>
              <div class="col-md-5">
                <div class="card-body">
                  <button
                    class="btn btn-primary specServ"
                    :class="{
                      selected: day.selectedService === 'license',
                      disabled: day.license >= day.licenseLimit,
                    }"
                    :disabled="day.license >= day.licenseLimit || day.disabled"
                    @click="selectService('license', index)"
                  >
                    <span>Licensing</span>
                    <span
                      class="counter"
                      :class="queueNumberColor(day.license, day.licenseLimit)"
                    >
                      {{ day.license }}/{{ day.licenseLimit }}
                    </span>
                    <span class="select">Select</span>
                  </button>
                  <button
                    class="btn btn-primary specServ"
                    :class="{
                      selected: day.selectedService === 'registration',
                      disabled: day.registration >= day.registrationLimit,
                    }"
                    :disabled="
                      day.registration >= day.registrationLimit || day.disabled
                    "
                    @click="selectService('registration', index)"
                  >
                    <span>Registration</span>
                    <span
                      class="counter"
                      :class="
                        queueNumberColor(
                          day.registration,
                          day.registrationLimit
                        )
                      "
                    >
                      {{ day.registration }}/{{ day.registrationLimit }}
                    </span>
                    <span class="select">Select</span>
                  </button>
                  <button
                    class="btn btn-primary specServ"
                    :class="{
                      selected: day.selectedService === 'LETAS',
                      disabled: day.LETAS >= day.LETASLimit,
                    }"
                    :disabled="day.LETAS >= day.LETASLimit || day.disabled"
                    @click="selectService('LETAS', index)"
                  >
                    <span>LETAS</span>
                    <span
                      class="counter"
                      :class="queueNumberColor(day.LETAS, day.LETASLimit)"
                    >
                      {{ day.LETAS }}/{{ day.LETASLimit }}
                    </span>
                    <span class="select">Select</span>
                  </button>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
      <img
        class="nextButton"
        :src="next"
        @click="goToNext"
        v-if="showNextButton"
      />
    </div>
    <div v-if="blur" class="overlay" @click="closeModal"></div>
    <div v-if="showModal" class="modal-box" style="padding: 0">
      <div style="display: flex; flex-direction: column">
        <div class="modalHeader" style="display: flex; padding: 1rem">
          <span style="font-size: 1rem; font-weight: 600">Select Service</span>
          <img
            :src="x"
            alt="x"
            style="margin-left: auto; cursor: pointer"
            @click="closeModal"
          />
        </div>
        <div style="height: 1px; width: 100%; background-color: #ced4da"></div>
        <div class="modalBody" style="padding: 1rem">
          <div class="list-group">
            <div
              v-for="service in specificServices[selectedServiceType]"
              :key="service.name"
              class="button-container"
            >
              <button
                type="button"
                class="list-group-item list-group-item-action d-flex justify-content-between align-items-center"
                :class="{ active: selectedSpecificService === service.name }"
                @click="selectSpecificService(service.name)"
                style="margin-top: 0"
              >
                {{ service.name }}
              </button>
              <div class="details-box">
                <p><strong>Details:</strong></p>
                <p>{{ service.details }}</p>
              </div>
            </div>
          </div>
        </div>
        <div style="height: 1px; width: 100%; background-color: #ced4da"></div>
        <div
          class="modalFooter"
          style="
            display: flex;
            margin-left: auto;
            gap: 0.5rem;
            padding: 0 1rem 1rem 1rem;
          "
        >
          <button type="button" class="btn btn-secondary" @click="closeModal">
            Cancel
          </button>
          <button
            type="button"
            class="btn btn-primary specbtn"
            style="border: none"
            @click="proceedToTicket"
          >
            Next
          </button>
        </div>
      </div>
    </div>
    <div v-if="showTicketModal" class="modal-box" style="padding: 0; margin: 0">
      <div style="display: flex; flex-direction: column">
        <div class="modalHeader" style="display: flex; padding: 1rem">
          <span style="font-size: 1rem; font-weight: 600"
            >Queue Ticket Confirmation</span
          >
          <img
            :src="x"
            alt="x"
            style="margin-left: auto; cursor: pointer"
            @click="closeModal"
          />
        </div>
        <div style="height: 1px; width: 100%; background-color: #ced4da"></div>
        <div class="modalBody" style="padding: 1rem">
          <span
            >You have successfully queued your ticket. View your ticket with the
            button below.</span
          >
        </div>
        <div style="height: 1px; width: 100%; background-color: #ced4da"></div>
        <div
          class="modalFooter"
          style="
            display: flex;
            margin-left: auto;
            gap: 0.5rem;
            padding: 0 1rem 1rem 1rem;
          "
        >
          <button type="button" class="btn btn-secondary" @click="closeModal">
            Close
          </button>
          <button
            type="button"
            class="btn btn-primary specbtn"
            style="border: none"
            @click="ticketRoute"
          >
            View Ticket
          </button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  import previous from "@/assets/previous.svg";
  import next from "@/assets/next.svg";
  import x from "@/assets/x-lg.svg";
  import navbar from "@/components/navbar.vue";
  import { supabase } from "../client/supabase";

  export default {
    components: { navbar },
    name: "scheduleBox",
    data() {
      return {
        previous,
        next,
        x,
        currentIndex: 0,
        twoWeeksDays: [],
        blur: false,
        showModal: false,
        showTicketModal: false,
        selectedServiceType: null, // Default selected type
        selectedSpecificService: "",
        specificServices: {
          license: [],
          registration: [],
          LETAS: [],
        },
        email: null,
        code: Array(6).fill(""),
        isActive: null,
        disabledDates: [],
      };
    },
    computed: {
      containerStyle() {
        const offset = -this.currentIndex * 100;
        return {
          transform: `translateX(${offset}%)`,
          transition: "transform 0.5s ease-in-out",
        };
      },
      showPrevButton() {
        return this.currentIndex > 0;
      },
      showNextButton() {
        return this.currentIndex < this.twoWeeksDays.length - 1;
      },
    },
    mounted() {
      this.getEmail();
    },
    methods: {
      async showServiceDetails() {
        let parent_id;

        if (this.selectedServiceType === "license") {
          parent_id = 1;
        } else if (this.selectedServiceType === "registration") {
          parent_id = 2;
        } else if (this.selectedServiceType === "LETAS") {
          parent_id = 3;
        }
        const { data, error } = await supabase
          .from("services")
          .select("service_name, service_description")
          .eq("parent_service_id", parent_id);

        this.specificServices[this.selectedServiceType] = data.map(
          (service) => ({
            name: service.service_name,
            details: service.service_description,
          })
        );

        if (error) {
          console.error("Error fetching service details:", error);
          return;
        }
      },
      async getQueueDetails() {
        const today = new Date(
          new Date().toLocaleString("en-US", { timeZone: "Asia/Manila" })
        );

        const services = [
          { id: 1, key: "DriverLicense", limit: "DriverLicenseLimit" },
          {
            id: 2,
            key: "VehicleRegistration",
            limit: "VehicleRegistrationLimit",
          },
          { id: 3, key: "LawEnforcement", limit: "LawEnforcementLimit" },
        ];

        // Build a date range for the next 5 days
        const dateRanges = Array.from({ length: 5 }, (_, i) => {
          const currentDay = new Date(today);
          currentDay.setDate(today.getDate() + i);
          const start = new Date(currentDay);
          start.setHours(0, 0, 0, 0); // Start of the day in local timezone
          const end = new Date(currentDay);
          end.setHours(23, 59, 59, 999); // End of the day in local timezone
          return {
            start,
            end,
          };
        });

        // Fetch Tickets
        const { data: tickets, error: ticketError } = await supabase
          .from("tickets")
          .select("service_id, parent_service_id, queue_date");

        if (ticketError) {
          console.error("Error fetching tickets:", error);
          return;
        }

        // Fetch Limits
        const { data: limits, error: limitError } = await supabase
          .from("queue_schedules")
          .select("date, service_name, limit");

        if (limitError) {
          console.error("Error fetching limits:", error);
        }

        // Process tickets locally
        services.forEach((service) => {
          const counts = Array(5).fill(0);

          dateRanges.forEach((range, i) => {
            counts[i] = tickets.filter((ticket) => {
              const queueDate = new Date(ticket.queue_date);
              return (
                (ticket.service_id === service.id ||
                  ticket.parent_service_id === service.id) &&
                queueDate >= new Date(range.start) &&
                queueDate <= new Date(range.end)
              );
            }).length;
          });
          this[service.key] = counts;
        });

        // Process limits locally
        const now = new Date();
        const date = new Date(now);
        const year = date.getFullYear();
        const day = String(date.getDate()).padStart(2, "0");
        const month = String(date.getMonth() + 1).padStart(2, "0");
        const formattedQueueDate = `${year}-${month}-${day}`;
        const startDate = new Date(formattedQueueDate);
        const daysRange = 5;

        services.forEach((service) => {
          this[service.limit] = new Array(daysRange).fill(0);

          limits
            .filter((item) => item.service_name === service.key)
            .forEach((item) => {
              const itemDate = new Date(item.date);
              const dayIndex = Math.floor(
                (itemDate - startDate) / (1000 * 60 * 60 * 24)
              );
              if (dayIndex >= 0 && dayIndex < daysRange) {
                this[service.limit][dayIndex] = item.limit;
              }
            });
        });

        // Define the range of dates
        const dateRange = Array.from({ length: daysRange }, (_, i) => {
          const date = new Date(startDate);
          date.setDate(date.getDate() + i);
          return date.toISOString().split("T")[0]; // Format as YYYY-MM-DD
        });

        // Fetch disabled dates
        const { data: is_disabled, error: disabledError } = await supabase
          .from("queue_dates")
          .select("is_disabled, date");

        // Process disabled dates
        if (disabledError) {
          console.error("Error fetching disabled dates:", disabledError);
        } else {
          // Map fetched data by date for quick lookup
          const disabledDatesMap = Object.fromEntries(
            is_disabled.map((item) => [item.date, item.is_disabled === "true"])
          );

          // Construct disabledDates array sorted by the defined range
          this.disabledDates = dateRange.map(
            (date) => disabledDatesMap[date] ?? null
          );
        }
      },
      goToNext() {
        if (this.currentIndex < this.twoWeeksDays.length - 1) {
          this.currentIndex++;
        }
      },
      goToPrevious() {
        if (this.currentIndex > 0) {
          this.currentIndex--;
        }
      },
      queueNumberColor(value, limit) {
        if (value >= limit * 0.75) return "red";
        if (value >= limit * 0.5) return "yellow";
        return "green";
      },
      getQueueLimit() {
        return 100;
      },
      resetToToday() {
        const today = new Date();
        const todayIndex = this.twoWeeksDays.findIndex(
          (day) => day.date.toDateString() === today.toDateString()
        );
        if (todayIndex !== -1) {
          this.currentIndex = todayIndex;
        }
      },
      selectService(service, index) {
        const selectedDay = this.twoWeeksDays[index];
        if (this.selectedServiceType && this.selectedServiceIndex !== index) {
          const previousSelectedDay =
            this.twoWeeksDays[this.selectedServiceIndex];
          previousSelectedDay.selectedService = null;
        }
        if (
          this.selectedServiceType === service &&
          this.selectedServiceIndex === index
        ) {
          this.selectedServiceType = null;
          this.selectedServiceIndex = null;
          selectedDay.selectedService = null;
          console.log(`Deselected ${service} on ${selectedDay.formattedDate}`);
        } else if (selectedDay[service] < 100) {
          this.selectedServiceType = service;
          this.selectedServiceIndex = index;
          selectedDay.selectedService = service;
          console.log(`Selected ${service} on ${selectedDay.formattedDate}`);
        } else {
          console.log(`${service} is full and cannot be selected.`);
        }
      },
      async showQueueModal(day) {
        this.selectedDay = day;
        this.selectedServiceType = day.selectedService || null;
        this.showModal = true;
        this.blur = true;

        await this.showServiceDetails();
      },
      closeModal() {
        this.showModal = false;
        this.showTicketModal = false;
        this.selectedServiceType = null;
        this.blur = false;
      },
      selectSpecificService(serviceName) {
        this.selectedSpecificService = serviceName;
      },
      addSpecificService(type, name, details) {
        if (this.specificServices[type]) {
          this.specificServices[type].push({ name, details });
        } else {
          this.$set(this.specificServices, type, [{ name, details }]);
        }
      },
      async getEmail() {
        const {
          data: { session },
          error,
        } = await supabase.auth.getSession();

        this.email = session.user.email;
      },
      async insertTicket() {
        let service;
        let parent_service;
        let transaction;
        let queue_time;

        const { data, error: specificError } = await supabase
          .from("services")
          .select(
            "service_id, parent_service_id, service_name, transaction_time"
          )
          .eq("service_name", this.selectedSpecificService);

        parent_service = data[0].parent_service_id;
        service = data[0].service_id;
        transaction = data[0].service_name;
        queue_time = data[0].transaction_time;

        const { count, error: countError } = await supabase
          .from("tickets")
          .select("service_id", { count: "exact", head: true })
          .eq("parent_service_id", parent_service)
          .gte("queue_date", `${this.selectedDay.formattedQueueDate} 00:00:00`)
          .lte("queue_date", `${this.selectedDay.formattedQueueDate} 23:59:59`);

        const { error } = await supabase.from("tickets").insert({
          ticket_number: count + 1,
          service_id: service,
          parent_service_id: parent_service,
          email: this.email,
          time_generated: new Date().toLocaleString("en-US", {
            timeZone: "Asia/Manila",
          }),
          queue_date: this.selectedDay.formattedQueueDate,
          transaction: transaction,
          status: "Pending",
          queue_time: queue_time,
          reference_number: Math.floor(Math.random() * 900000) + 100000,
        });
      },
      async proceedToTicket() {
        const { data, error } = await supabase
          .from("tickets")
          .select("email")
          .eq("email", this.email);

        if (!data || data.length === 0) {
          this.showModal = false;
          this.showTicketModal = true;
          this.insertTicket();
        } else {
          alert("You already queued!");
        }
      },
      ticketRoute() {
        this.$router.push({ name: "ticket" });
      },
      goBackModal() {
        this.showEmailModal = false;
        this.showModal = true;
      },
    },
    created() {
      this.getQueueDetails().then(() => {
        const days = [];
        const today = new Date();

        for (let i = 0; i < 5; i++) {
          const date = new Date(today);
          date.setDate(today.getDate() + i);

          const formattedDay = date.toLocaleDateString("en-US", {
            weekday: "long",
          });
          const year = date.getFullYear();
          const day = String(date.getDate()).padStart(2, "0");
          const month = String(date.getMonth() + 1).padStart(2, "0");
          const formattedDate = `${month}.${day}`;
          const formattedQueueDate = `${year}-${month}-${day}`;
          days.push({
            formattedDay,
            formattedDate,
            formattedQueueDate,
            date,
            license: this.DriverLicense[i],
            registration: this.VehicleRegistration[i],
            LETAS: this.LawEnforcement[i],
            selectedService: null,
            licenseLimit: this.DriverLicenseLimit[i] || 100,
            registrationLimit: this.VehicleRegistrationLimit[i] || 100,
            LETASLimit: this.LawEnforcementLimit[i] || 100,
            disabled: this.disabledDates[i] || false,
          });
        }
        this.twoWeeksDays = days;
      });
    },
  };
</script>

<style scoped>
  .navbar {
    position: relative;
    z-index: 998;
  }

  .scheduleBox {
    background: #dee2e6;
  }

  .boxArea {
    width: 100%;
    display: flex;
    justify-content: center;
    align-items: center;
    position: relative;
    overflow: hidden;
  }

  h1 {
    font-weight: 800 !important;
    padding-top: 2.43rem;
    padding-bottom: 1rem;
  }

  h3 {
    font-size: 1.7rem;
  }

  h2 {
    font-size: 2.5rem;
  }

  h2,
  h3 {
    font-weight: bold;
  }

  .boxContainer {
    display: flex;
    flex-wrap: nowrap;
    transition: transform 0.5s ease-in-out;
    width: 100%;
  }

  .card-group {
    min-width: 100%;
    display: flex;
    justify-content: center;
    align-items: center;
  }

  .row {
    display: flex;
    height: 100%;
    padding: 2rem 1.5rem 2rem 1.5rem;
    flex-wrap: nowrap;
    flex-shrink: 0;
    transition: transform 0.5s ease;
  }

  .dateCardContent {
    display: flex;
    align-items: center;
    justify-content: space-between;
    width: 88%;
    height: 60%;
    border: 1px solid #dee2e6;
    border-radius: 1rem;
    padding: 2rem;
  }

  .disabled-card {
    opacity: 0.5;
    pointer-events: none;
  }

  .disabled-btn {
    background-color: #ccc;
    cursor: not-allowed;
  }

  .dateTime {
    display: flex;
    flex-direction: column;
  }

  .card-title {
    margin: 0;
  }

  .col-md-1 {
    width: 2.2rem;
  }

  .col-md-6 {
    display: flex;
    flex-direction: column;
    justify-content: space-between;
    height: 100%;
    position: relative;
  }

  .line {
    width: 1px;
    height: 98%;
    background: black;
  }

  .backToToday {
    color: #68717a;
    text-decoration: underline;
    cursor: pointer;
    margin-top: auto;
    text-align: center;
  }

  .specServ {
    display: flex;
    align-items: center;
    background-color: #6ea8fe;
    width: 20.625rem;
    height: 5.125rem;
    margin-bottom: 0.7rem;
    border-radius: 1rem;
    border: none;
    box-shadow: 3px 3px 3px rgba(0, 0, 0, 0.1);
    font-size: 1.75rem;
    font-weight: bold;
    padding-left: 1.7rem;
    padding-right: 1rem;
  }

  .selected {
    background-color: #007bff;
    box-shadow: 3px 3px 3px rgba(0, 0, 0, 0.1);
  }

  .counter {
    display: flex;
    align-items: center;
    justify-content: center;
    width: 3.5625rem;
    height: 1.25rem;
    background-color: #ebe5fc;
    margin-left: 0.3rem;
    border-radius: 1rem;
    font-size: 0.625rem;
  }

  .select {
    display: flex;
    font-size: 0.75rem;
    color: #68717a;
    font-weight: lighter;
    margin-left: auto;
    text-decoration: underline;
  }

  .red {
    color: #dc3545;
  }

  .yellow {
    color: #fd7e14;
  }

  .green {
    color: #198754;
  }

  .prevButton,
  .nextButton {
    position: absolute;
    top: 50%;
    transform: translateY(-50%);
    cursor: pointer;
    width: 2rem;
    height: 2rem;
    z-index: 10;
  }

  .prevButton {
    left: 10rem;
  }

  .nextButton {
    right: 10rem;
  }

  .smallerFont {
    font-size: 2rem;
  }

  .overlay {
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background: rgba(0, 0, 0, 0.5);
    backdrop-filter: blur(10px);
    z-index: 999;
  }

  .modal-box {
    position: fixed;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
    padding: 20px;
    background-color: white;
    border-radius: 10px;
    box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1);
    z-index: 1000;
    width: 38.9375rem;
    text-align: center;
  }

  .modal-box button {
    margin-top: 20px;
    padding: 10px 20px;
  }

  .specbtn {
    background-color: #084298;
  }

  .specbtn:hover {
    background-color: #052c65;
  }

  .selected {
    background-color: #084298;
    color: white;
  }

  .numContainer {
    display: flex;
    justify-content: center;
    align-items: center;
    gap: 10px;
    width: 100%;
    margin-bottom: 1rem;
  }

  .num {
    width: 57px;
    height: 78px;
    box-sizing: border-box;
    border-radius: 20px;
    border: none;
    background-color: #f0f1f5;
    background-position: 10px center;
    background-repeat: no-repeat;
    padding-left: 22px;
    font-size: 30px;
  }

  .details-box {
    position: absolute;
    top: 50%;
    left: 105%;
    /* Adjust based on the desired spacing */
    transform: translateY(-50%);
    width: 200px;
    padding: 10px;
    background-color: #f8f9fa;
    /* Light gray background */
    border: 1px solid #ddd;
    /* Border color */
    border-radius: 5px;
    box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
    /* Subtle shadow */
    opacity: 0;
    visibility: hidden;
    transition: opacity 0.3s ease, visibility 0.3s ease;
    z-index: 1000;
  }

  .button-container:hover .details-box {
    opacity: 1;
    visibility: visible;
  }
</style>
