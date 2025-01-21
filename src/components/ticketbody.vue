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
      <button class="refresh-button" @click="findRef">
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
      async convertMinutes(minutes, transaction, ticket_number) {
        let totalRemainingTime;
        const now = new Date();
        const date = new Date(now);
        const year = date.getFullYear();
        const day = String(date.getDate()).padStart(2, "0");
        const month = String(date.getMonth() + 1).padStart(2, "0");
        const formattedQueueDate = `${year}-${month}-${day}`;
        const { data, error } = await supabase
          .from("tickets")
          .select("queue_time, ticket_number")
          .eq("transaction", transaction)
          .gte("queue_date", `${formattedQueueDate} 00:00:00`)
          .lte("queue_date", `${formattedQueueDate} 23:59:59`)
          .neq("status", "Reject")
          .neq("status", "Complete")

        const filteredData = data.filter(
          (item) => item.ticket_number < ticket_number
        );
        if (filteredData == 0) {
          totalRemainingTime = 1
        } else{
          totalRemainingTime = Math.ceil((filteredData.length) / 10);
        }
        
        const totalMinutes = minutes * totalRemainingTime 
        const hours = Math.floor(totalMinutes / 60);
        const remainingMinutes = totalMinutes % 60;

        if (hours === 0) {
          if (remainingMinutes === 1) return `${remainingMinutes} minute`;
          return `${remainingMinutes} minutes`;
        } else if (remainingMinutes === 0) {
          if (hours === 1) return `${hours} hour`;
          return `${hours} hours`;
        } else {
          return `${hours} hours and ${remainingMinutes} minutes`;
        }
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
            .eq("email", session.user.email)
            .neq("status", "Complete")
            .neq("status", "Reject");

          if (data.length === 0) {
            this.noTicketIsVisible = true;
            return;
          }
          if (data && data.length > 0) {
            this.queueNumber = String(data[0].ticket_number).padStart(3, "0");
            this.transaction = data[0].transaction;
            this.estimatedWait = await this.convertMinutes(
              data[0].queue_time,
              data[0].transaction,
              data[0].ticket_number
            );
            this.queueDate = data[0].queue_date;
            this.referenceNumber = data[0].reference_number;
            this.status = data[0].status;
          } else {
            this.noTicketIsVisible = true;
          }
        }
      },
      async findRef() {
        if (!this.referenceNumber) {
          this.referenceNumber = this.reference;
        }
        const { data, error } = await supabase
          .from("tickets")
          .select(
            "ticket_number, transaction, queue_time, reference_number, status, queue_date"
          )
          .eq("reference_number", this.referenceNumber)
          .neq("status", "Complete")
          .neq("status", "Reject");

        if (data.length === 0) {
          this.noTicketIsVisible = true;
          return;
        }
        if (data && data.length > 0) {
          this.queueDate = data[0].queue_date;
          this.queueNumber = String(data[0].ticket_number).padStart(3, "0");
          this.transaction = data[0].transaction;
          this.estimatedWait = await this.convertMinutes(
            data[0].queue_time,
            data[0].transaction,
            data[0].ticket_number
          );
          this.referenceNumber = data[0].reference_number;
          this.status = data[0].status;
          this.noTicketIsVisible = false;
        }
      },
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
