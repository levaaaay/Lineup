<template>
    <div class="staffSchedBox">
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
                  >
                    <div class="dateTime">
                      <h3 class="card-title">
                        {{ day.formattedDay }}
                      </h3>
                      <h2 class="card-title">{{ day.formattedDate }}</h2>
                    </div>
                    <button
                      class="btn btn-primary specbtn"
                      @click="disable(day)"
                      style="
                        background-color: #052c65;
                        border: none;
                        width: 8.625rem;
                        height: 3.125rem;
                      "
                    >
                      Disable Day
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
                      @click="selectService('license', index)"
                    >
                      <span>Licensing</span>
                      <span class="counter">
                        {{ day.licenseLimit }}
                      </span>
                      <span class="select">Edit Limit</span>
                    </button>
                    <button
                      class="btn btn-primary specServ"
                      @click="selectService('registration', index)"
                    >
                      <span>Registration</span>
                      <span class="counter">
                        {{ day.registrationLimit }}
                      </span>
                      <span class="select">Edit Limit</span>
                    </button>
                    <button
                      class="btn btn-primary specServ"
                      @click="selectService('LETAS', index)"
                    >
                      <span>LETAS</span>
                      <span class="counter">
                        {{ day.LETASLimit }}
                      </span>
                      <span class="select">Edit Limit</span>
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
            <span style="font-size: 1rem; font-weight: 600">Enter Queue Limit</span>
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
    </div>
  </template>
  
  <script>
    import previous from "@/assets/previous.svg";
    import next from "@/assets/next.svg";
    import x from "@/assets/x-lg.svg";
    import navbar from "@/components/navbar.vue";
    import { supabase } from "@/client/supabase";
  
    export default {
      components: { navbar },
      name: "staffSchedBox",
      data() {
        return {
          previous,
          next,
          x,
          currentIndex: 0,
          twoWeeksDays: [],
          blur: false,
          showModal: false,
          licenseLimit: 0,
          registrationLimit: 0,
          LETASLimit: 0,
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
          const today = new Date(
            new Date().toLocaleString("en-US", { timeZone: "Asia/Manila" })
          );
  
          this.DriverLicense = [];
          this.VehicleRegistration = [];
          this.LawEnforcement = [];
  
          for (let i = 0; i < 5; i++) {
            const currentDay = new Date(today);
            currentDay.setDate(today.getDate() + i);
            const dateString = currentDay.toLocaleDateString("en-CA");
  
            const { count: DriverLicenseCount, error: DriverLicenseCountError } =
              await supabase
                .from("tickets")
                .select("service_id", { count: "exact", head: true })
                .or("service_id.eq.1,parent_service_id.eq.1")
                .gte("queue_date", `${dateString} 00:00:00`)
                .lte("queue_date", `${dateString} 23:59:59`);
  
            if (DriverLicenseCountError) {
              console.error(DriverLicenseCountError);
            }
  
            const {
              count: VehicleRegistrationCount,
              error: VehicleRegistrationCountError,
            } = await supabase
              .from("tickets")
              .select("service_id", { count: "exact", head: true })
              .or("service_id.eq.2,parent_service_id.eq.2")
              .gte("queue_date", `${dateString} 00:00:00`)
              .lte("queue_date", `${dateString} 23:59:59`);
  
            if (VehicleRegistrationCountError) {
              console.error(VehicleRegistrationCountError);
            }
  
            const {
              count: LawEnforcementCount,
              error: LawEnforcementCountError,
            } = await supabase
              .from("tickets")
              .select("service_id", { count: "exact", head: true })
              .or("service_id.eq.3,parent_service_id.eq.3")
              .gte("queue_date", `${dateString} 00:00:00`)
              .lte("queue_date", `${dateString} 23:59:59`);
  
            if (LawEnforcementCountError) {
              console.error(LawEnforcementCountError);
            }
  
            this.DriverLicense[i] = DriverLicenseCount;
            this.VehicleRegistration[i] = VehicleRegistrationCount;
            this.LawEnforcement[i] = LawEnforcementCount;
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
          this.showModal = true;
          this.blur = true;
        },
        closeModal() {
          this.showModal = false;
          this.blur = false;
        },
        ticketRoute() {
          this.$router.push({ name: "ticket" });
        },
      },
      created() {
        this.showServiceQueueNumber().then(() => {
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
  
    .staffSchedBox {
      background: #dee2e6;
      height: 100vh;
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
  </style>
  