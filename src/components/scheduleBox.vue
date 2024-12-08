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
          :class="{ current: index === currentIndex }"
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
                      disabled: day.license >= 100,
                    }"
                    :disabled="day.license >= 100"
                    @click="selectService('license', index)"
                  >
                    <span>Licensing</span>
                    <span
                      class="counter"
                      :class="queueNumberColor(day.license)"
                    >
                      {{ day.license }}/100
                    </span>
                    <span class="select">Select</span>
                  </button>
                  <button
                    class="btn btn-primary specServ"
                    :class="{
                      selected: day.selectedService === 'registration',
                      disabled: day.registration >= 100,
                    }"
                    :disabled="day.registration >= 100"
                    @click="selectService('registration', index)"
                  >
                    <span>Registration</span>
                    <span
                      class="counter"
                      :class="queueNumberColor(day.registration)"
                    >
                      {{ day.registration }}/100
                    </span>
                    <span class="select">Select</span>
                  </button>
                  <button
                    class="btn btn-primary specServ"
                    :class="{
                      selected: day.selectedService === 'LETAS',
                      disabled: day.LETAS >= 100,
                    }"
                    :disabled="day.LETAS >= 100"
                    @click="selectService('LETAS', index)"
                  >
                    <span>LETAS</span>
                    <span class="counter" :class="queueNumberColor(day.LETAS)">
                      {{ day.LETAS }}/100
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
            <button
              type="button"
              class="list-group-item list-group-item-action d-flex justify-content-between align-items-center"
              aria-current="true"
              :class="{
                active:
                  selectedSpecificService ===
                  'Sales Reporting and Registration of Motor Vehicles',
              }"
              @click="
                selectSpecificService(
                  'Sales Reporting and Registration of Motor Vehicles'
                )
              "
              style="margin-top: 0"
            >
              Sales Reporting and Registration of Motor Vehicles
              <span class="badge bg-primary rounded-pill">14</span>
            </button>
            <button
              type="button"
              class="list-group-item list-group-item-action d-flex justify-content-between align-items-center"
              :class="{
                active: selectedSpecificService === 'Vehicle Encoding/Linking',
              }"
              @click="selectSpecificService('Vehicle Encoding/Linking')"
              style="margin-top: 0"
            >
              Vehicle Encoding/Linking
              <span class="badge bg-primary rounded-pill">14</span>
            </button>
            <button
              type="button"
              class="list-group-item list-group-item-action d-flex justify-content-between align-items-center"
              :class="{
                active:
                  selectedSpecificService ===
                  'Renewal of Motor Vehicle Registration',
              }"
              @click="
                selectSpecificService('Renewal of Motor Vehicle Registration')
              "
              style="margin-top: 0"
            >
              Renewal of Motor Vehicle Registration
              <span class="badge bg-primary rounded-pill">14</span>
            </button>
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
            @click="proceedToEmail"
          >
            Next
          </button>
        </div>
      </div>
    </div>
    <div v-if="showEmailModal" class="modal-box" style="padding: 0">
      <div style="display: flex; flex-direction: column">
        <div class="modalHeader" style="display: flex; padding: 1rem">
          <span style="font-size: 1rem; font-weight: 600">Enter Email</span>
          <img
            :src="x"
            alt="x"
            style="margin-left: auto; cursor: pointer"
            @click="closeModal"
          />
        </div>
        <div style="height: 1px; width: 100%; background-color: #ced4da"></div>
        <div class="modalBody" style="padding: 1rem">
          <div class="input-group mb-3">
            <input
              type="text"
              class="form-control"
              placeholder="Email Address"
              aria-label="Email Address"
              aria-describedby="basic-addon1"
              v-model="email"
            />
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
          <button type="button" class="btn btn-secondary" @click="goBackModal">
            Return
          </button>
          <button
            type="button"
            class="btn btn-primary specbtn"
            style="border: none"
            @click="proceedToVerify"
          >
            Next
          </button>
        </div>
      </div>
    </div>
    <div v-if="showVerifyModal" class="modal-box" style="padding: 0">
      <div style="display: flex; flex-direction: column">
        <div class="modalHeader" style="display: flex; padding: 1rem">
          <span style="font-size: 1rem; font-weight: 600">Verify Email</span>
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
            >We have sent an OTP to your entered email address. Kindly input the
            OTP in the space provided below.</span
          >
        </div>
        <div class="numContainer">
          <div class="numbox" v-for="(digit, index) in code" :key="index">
            <form>
              <input
                type="text"
                required
                class="num"
                maxlength="1"
                inputmode="numeric"
                @input="validateInput($event)"
                v-model="code[index]"
              />
            </form>
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
          <button type="button" class="btn btn-secondary" @click="goBackEmail">
            Return
          </button>
          <button
            type="button"
            class="btn btn-primary specbtn"
            style="border: none"
            @click="proceedToTicket"
          >
            Confirm
          </button>
        </div>
      </div>
    </div>
    <div v-if="showTicketModal" class="modal-box" style="padding: 0">
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
          <button type="button" class="btn btn-secondary" @click="close">
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
        showEmailModal: false,
        showVerifyModal: false,
        showTicketModal: false,
        selectedServiceType: null,
        selectedSpecificService: null,
        email: null,
        code: Array(6).fill(""),
        queueCount: [],
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
    methods: {
      async showServiceQueueNumber() {
        const { count: DriverLicenseCount, error: DriverLicenseCountError } =
          await supabase
            .from("tickets")
            .select("service_id", { count: "exact", head: true })
            .or("service_id.eq.1,parent_service_id.eq.1");

        if (DriverLicenseCountError) {
          console.error(DriverLicenseCountError);
        }

        const {
          count: VehicleRegistrationCount,
          error: VehicleRegistrationCountError,
        } = await supabase
          .from("tickets")
          .select("service_id", { count: "exact", head: true })
          .or("service_id.eq.2,parent_service_id.eq.2");

        if (VehicleRegistrationCountError) {
          console.error(VehicleRegistrationCountError);
        }

        const { count: LawEnforcementCount, error: LawEnforcementCountError } =
          await supabase
            .from("tickets")
            .select("service_id", { count: "exact", head: true })
            .or("service_id.eq.3,parent_service_id.eq.3");

        if (LawEnforcementCountError) {
          console.error(LawEnforcementCountError);
        }
        this.queueCount = [
          DriverLicenseCount,
          VehicleRegistrationCount,
          LawEnforcementCount,
        ];
      },
      generateTwoWeeks() {
        const days = [];
        const today = new Date();

        for (let i = 0; i < 14; i++) {
          const date = new Date(today);
          date.setDate(today.getDate() + i);

          const formattedDay = date.toLocaleDateString("en-US", {
            weekday: "long",
          });
          const day = String(date.getDate()).padStart(2, "0");
          const month = String(date.getMonth() + 1).padStart(2, "0");
          const formattedDate = `${month}.${day}`;
          days.push({
            formattedDay,
            formattedDate,
            date,
            license: this.queueCount[0],
            registration: Math.floor(Math.random() * 101),
            LETAS: Math.floor(Math.random() * 101),
            selectedService: null,
          });
        }
        return days;
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
      queueNumberColor(value) {
        if (value > 76) return "red";
        if (value > 50) return "yellow";
        return "green";
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
      showQueueModal(day) {
        this.selectedDay = day;
        this.selectedServiceType = day.selectedService || null;
        this.showModal = true;
        this.blur = true;
      },
      closeModal() {
        this.showModal = false;
        this.selectedDay = null;
        this.selectedServiceType = null;
        this.blur = false;
      },
      close() {
        this.showModal = false;
        this.blur = false;
      },
      selectSpecificService(service) {
        if (this.selectedSpecificService === service) {
          this.selectedSpecificService = null;
        } else {
          this.selectedSpecificService = service;
        }
      },
      async proceedToEmail() {
        if (this.selectedSpecificService) {
          this.showModal = false;
          this.showEmailModal = true;
        }
      },
      async proceedToVerify() {
        if (this.email) {
          const { data, error } = await supabase
            .from("tickets")
            .select("email")
            .eq("email", this.email);

          if (data.length == 1) {
            console.log(data);
            alert("You already queued!");
          } else {
            const { data, error } = await supabase.auth.signInWithOtp({
              email: this.email,
              options: {
                shouldCreateUser: true,
              },
            });
            this.showEmailModal = false;
            this.showVerifyModal = true;
          }
        } else {
          alert("Enter Valid Email!");
        }
      },
      async insertTicket() {
        if (
          this.selectedSpecificService ===
          "Sales Reporting and Registration of Motor Vehicles"
        ) {
          const { count: motorRegistration, error: motorRegistrationError } =
            await supabase
              .from("tickets")
              .select("service_id", { count: "exact", head: true })
              .eq("service_id", 7);
          const { error } = await supabase.from("tickets").insert({
            ticket_number: motorRegistration + 1,
            service_id: 9,
            parent_service_id: 2,
            email: this.email,
          });
        }
      },
      async proceedToTicket() {
        const {
          data: { session },
          error,
        } = await supabase.auth.verifyOtp({
          email: this.email,
          token: this.code.join(""),
          type: "email",
        });
        if (error) {
          console.log(error);
          alert("Invalid OTP! Check and enter again.");
        } else {
          this.showVerifyModal = false;
          this.showTicketModal = true;
          this.insertTicket();
        }
      },
      ticketRoute() {
        this.$router.push({ name: "ticket" });
      },
      goBackModal() {
        this.showEmailModal = false;
        this.showModal = true;
      },
      goBackEmail() {
        this.showEmailModal = true;
        this.showVerifyModal = false;
      },
      validateInput(event) {
        const input = event.target;
        if (!/^\d*$/.test(input.value)) {
          input.value = "";
        }
      },
    },
    created() {
      this.showServiceQueueNumber().then(() => {
        const days = [];
        const today = new Date();

        for (let i = 0; i < 14; i++) {
          const date = new Date(today);
          date.setDate(today.getDate() + i);

          const formattedDay = date.toLocaleDateString("en-US", {
            weekday: "long",
          });
          const day = String(date.getDate()).padStart(2, "0");
          const month = String(date.getMonth() + 1).padStart(2, "0");
          const formattedDate = `${month}.${day}`;
          days.push({
            formattedDay,
            formattedDate,
            date,
            license: this.queueCount[0],
            registration: this.queueCount[1],
            LETAS: this.queueCount[2],
            selectedService: null,
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
</style>
