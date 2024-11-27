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
          <span style="font-weight: 600; font-size: 1.5rem"
            >You do not have a ticket yet</span
          >
          <button class="queue" @click="gotoSchedule">Queue now</button>
        </div>
      </div>
      <div class="ticket" v-if="!noTicketIsVisible">
        <div class="ticketBorder" style="justify-content: flex-start">
          <div class="progressBar"></div>
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
          <button class="queue" style="font-size: 0.9rem; font-weight: 500">
            View Routing Slip
          </button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  export default {
    name: "ticketbody",
    data() {
      return {
        noTicketIsVisible: false,
        queueNumber: "001",
        transaction: "Renewal of Motor Vehicle (MV) Registration",
        estimatedWait: "2 hours 0 minutes 0 seconds",
        referenceNumber: "2024231102001",
      };
    },
    methods: {
      gotoSchedule() {
        this.$router.push("schedule");
      },
      async showTicketDetails() {
        const { data, error } = await supabase
          .from("tickets")
          .select("ticket_number, queue_time, reference_number")
          .eq("email", email);

        if (error) {
          console.error(error);
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
    height: 50vh;
    background-color: white;
  }

  .ticketBorder {
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    width: 33vw;
    height: 41vh;
    border: 5px solid black;
    border-radius: 10px;
    padding: 1rem 0 0 0;
  }

  .queue {
    display: flex;
    justify-content: center;
    align-items: center;
    width: 10rem;
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
    margin-bottom: 1vh;
    padding-left: 2vh;
    font-size: 0.9vw;
  }

  .boldtext {
    color: #68717a;
    font-weight: 700;
  }

  .progressBar {
    width: 28vw;
    height: 0.9375rem;
    background-color: #dee2e6;
    margin-bottom: 2vh;
  }
</style>
