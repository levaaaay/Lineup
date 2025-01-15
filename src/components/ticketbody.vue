<template>
  <div class="ticketbody" style="height: 83vh; background-color: #dee2e6">
    <div class="header" style="display: flex; justify-content: center">
      <h1 style="padding: 2rem 0 0 0">Ticket</h1>
    </div>
    <div style="display: flex; justify-content: center">
      <div
        class="dispenser"
        style="
          width: 53.5rem;
          height: 5px;
          background-color: #adadad;
          border-radius: 10px;
        "
      ></div>
    </div>
    <div style="display: flex; justify-content: center; align-items: center">
      <div class="ticket" v-if="noTicketIsVisible">
        <div class="ticketBorder">
          <p style="font-weight: 700; font-size: 1rem">
            Enter Reference Number
          </p>
          <div
            style="
              display: flex;
              align-items: center;
              gap: 0.5rem;
              margin: 1rem 1rem 1rem 1rem;
            "
          >
            <input
              type="text"
              class="form-control"
              placeholder="Reference #"
              aria-label="reference"
              aria-describedby="basic-addon1"
              v-model="reference"
              style="width: 20vw"
            />
            <button
              @click="findRef"
              style="
                width: 4.9375rem;
                height: 2rem;
                background-color: #084298;
                border: none;
                border-radius: 5px;
                color: white;
                font-size: 0.875rem;
              "
            >
              Confirm
            </button>
          </div>
          <div style="color: #68717a; padding: 1rem 1rem 2rem 1rem">
            -------------------- or --------------------
          </div>
          <button class="queue" @click="gotoSchedule">Queue now</button>
        </div>
      </div>
      <div class="ticket" v-if="!noTicketIsVisible">
        <div class="ticketBorder" style="justify-content: flex-start">
          <div class="infobox">
            <span class="boldtext">Date: </span>
            <span style="color: #084298; font-weight: 700; margin-left: 0.5vw">
              {{ queueDate }}</span
            >
          </div>
          <div class="infobox">
            <span class="boldtext">Queue Number: </span>
            <span style="color: #084298; font-weight: 700; margin-left: 0.5vw">
              {{ queueNumber }}</span
            >
          </div>
          <div class="infobox">
            <span class="boldtext">Transaction: </span>
            <span style="color: #68717a; margin-left: 0.5vw">
              {{ transaction }}</span
            >
          </div>
          <div class="infobox">
            <span class="boldtext">Estimated Waiting Time: </span>
            <span style="color: #68717a; margin-left: 0.5vw">
              {{ estimatedWait }}</span
            >
          </div>
          <div class="infobox">
            <span class="boldtext">Reference Number: </span>
            <span style="color: #68717a; margin-left: 0.5vw">
              {{ referenceNumber }}</span
            >
          </div>
          <div class="infobox">
            <span class="boldtext">Status: </span>
            <span style="color: #68717a; margin-left: 0.5vw">
              {{ status }}</span
            >
          </div>
        </div>
      </div>
    </div>
    <div class="refreshcontainer">
      <button class="refresh-button" @click="updateTicket">
        <img :src="refreshButton" alt="Refresh" />
      </button>
    </div>
  </div>
</template>

<script>
  import { supabase } from "../client/supabase";
  import refreshButton from "@/assets/refreshButton.svg";

  export default {
    name: "ticketbody",
    data() {
      return {
        noTicketIsVisible: false,
        queueDate: null,
        queueNumber: null,
        transaction: null,
        estimatedWait: null,
        referenceNumber: null,
        status: null,
        reference: "",
        refreshButton,
      };
    },
    mounted() {
      this.showTicketDetails();
    },
    methods: {
      gotoSchedule() {
        this.$router.push("schedule");
      },
      calculateRemainingTime(timeGenerated, estimatedMinutes, queueDate) {
        const date = new Date(timeGenerated);
        // Get hours, minutes, and seconds
        const hours = String(date.getUTCHours()).padStart(2, "0"); // Use getUTCHours for UTC time
        const minutes = String(date.getUTCMinutes()).padStart(2, "0");
        const seconds = String(date.getUTCSeconds()).padStart(2, "0");
        const generatedDate = new Date();
        generatedDate.setHours(hours, minutes, seconds);

        const year = date.getFullYear();
        const day = String(date.getDate()).padStart(2, "0");
        const month = String(date.getMonth() + 1).padStart(2, "0");
        const formattedQueueDate = `${year}-${month}-${day}`;

        if (formattedQueueDate !== queueDate) {
          return "N/A";
        }

        const currentTime = new Date();
        const timeDifference = currentTime - generatedDate;
        const remainingMinutes =
          estimatedMinutes - Math.floor(timeDifference / 60000);

        if (remainingMinutes <= 0) {
          return "0";
        }

        return `${remainingMinutes} Minutes`;
      },
      async showTicketDetails() {
        const {
          data: { session },
          error,
        } = await supabase.auth.getSession();

        if (session) {
          const { data, error } = await supabase
            .from("tickets")
            .select(
              "email, ticket_number, transaction, queue_time, reference_number, status, time_generated, queue_date"
            )
            .eq("email", session.user.email);

          if (data && data.length > 0) {
            this.queueNumber = String(data[0].ticket_number).padStart(3, "0");
            this.transaction = data[0].transaction;
            this.estimatedWait = this.calculateRemainingTime(
              data[0].time_generated,
              data[0].queue_time,
              data[0].queue_date
            );
            this.queueDate = data[0].queue_date;
            this.referenceNumber = data[0].reference_number;
            this.status = data[0].status;
          } else {
            this.noTicketIsVisible = true;
          }
        }
      },
    },
    async updateTicket() {
      const {
        data: { session },
        error: sessionError,
      } = await supabase.auth.getSession();

      if (session) {
        const query = supabase
          .from("tickets")
          .select(
            "email, ticket_number, transaction, queue_time, reference_number, status"
          );

        // Build dynamic filter based on whether `this.reference` is provided
        if (this.reference) {
          query.or(
            `email.eq.${session.user.email},reference_number.eq.${this.reference}`
          );
        } else {
          query.eq("email", session.user.email);
        }

        const { data, error } = await query;

        if (error) {
          console.error(error);
        } else if (data && data.length > 0) {
          this.queueNumber = String(data[0].ticket_number).padStart(3, "0");
          this.transaction = data[0].transaction;
          this.estimatedWait = data[0].queue_time;
          this.referenceNumber = data[0].reference_number;
          this.status = data[0].status;
        }
      }
    },
    async findRef() {
      const { data, error } = await supabase
        .from("tickets")
        .select(
          "ticket_number, transaction, queue_time, reference_number, status"
        )
        .eq("reference_number", this.reference);

      if (data && data.length > 0) {
        console.log(data[0]);
        this.queueNumber = String(data[0].ticket_number).padStart(3, "0");
        this.transaction = data[0].transaction;
        this.estimatedWait = data[0].queue_time;
        this.referenceNumber = data[0].reference_number;
        this.status = data[0].status;
        this.noTicketIsVisible = false;
      }
    },
  };
</script>

<style scoped>
  .ticket {
    display: flex;
    justify-content: center;
    align-items: center;
    width: 37.5vw;
    height: 52vh;
    background-color: white;
  }

  .ticketBorder {
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    width: 33vw;
    height: 43vh;
    border: 5px solid #031633;
    border-radius: 10px;
    padding: 1rem 0 0 0;
  }

  .queue {
    display: flex;
    justify-content: center;
    align-items: center;
    width: 8.625rem;
    height: 3rem;
    border: none;
    background-color: #084298;
    border-radius: 10px;
    color: white;
    font-weight: 600;
  }

  .queue:hover {
    background-color: #085ad4;
  }

  .infobox {
    display: flex;
    align-items: center;
    width: 28vw;
    height: 5vh;
    background-color: white;
    border: 1px solid #dee2e6;
    border-radius: 10px;
    margin-bottom: 1.5vh;
    padding-left: 2vh;
    font-size: 0.9vw;
  }

  .boldtext {
    color: #68717a;
    font-weight: 700;
  }

  .refresh-button {
  background-color: #084298;
  border: none;
  border-radius: 50%;
  width: 3rem;
  height: 3rem;
  display: flex;
  justify-content: center;
  align-items: center;
  cursor: pointer;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
}

.refresh-button img {
  width: 2.5rem;
  height: 2.5rem;
  filter: invert(1);
}

.refresh-button:hover {
  background-color: #085ad4;
}

.refreshcontainer {
  display: flex;
  justify-content: flex-end;
  margin-right: 20rem;
}
</style>
