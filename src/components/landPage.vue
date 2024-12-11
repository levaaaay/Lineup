<template>
  <div class="landPage">
    <div class="landPageHeader">
      <h1 class="text-center">{{ headerLine1 }}</h1>
    </div>
    <div class="logos">
      <div class="logosSlide">
        <img class="comingSoon" :src="prcLogo" alt="PRC Logo" />
        <img class="comingSoon" :src="dfaLogo" alt="DFA Logo" />
        <img :src="ltoLogo" alt="LTO Logo" />
        <img class="comingSoon" :src="birLogo" alt="BIR Logo" />
        <img class="comingSoon" :src="psaLogo" alt="PSA Logo" />
      </div>
      <div class="logosSlide">
        <img class="comingSoon" :src="prcLogo" alt="PRC Logo" />
        <img class="comingSoon" :src="dfaLogo" alt="DFA Logo" />
        <img :src="ltoLogo" alt="LTO Logo" />
        <img class="comingSoon" :src="birLogo" alt="BIR Logo" />
        <img class="comingSoon" :src="psaLogo" alt="PSA Logo" />
      </div>
    </div>
    <div class="queueText">
      <div class="dynamic">{{ queueNumber }}</div>
      <span>{{ queueText }}</span>
    </div>
    <div class="queueNowButton">
      <button class="btn btn-primary" @click="queue">Queue Now</button>
    </div>
    <div class="signOutButton">
      <button class="btn btn-primary" @click="SignOut">Sign out</button>
    </div>   
  </div>
</template>

<script>
  import ltoLogo from "@/assets/ltoLogo.svg";
  import dfaLogo from "@/assets/dfaLogo.svg";
  import prcLogo from "@/assets/prcLogo.svg";
  import birLogo from "@/assets/birLogo.svg";
  import psaLogo from "@/assets/psaLogo.svg";
  import { supabase } from "../client/supabase";

  export default {
    name: "landPage",
    data() {
      return {
        headerLine1: "Queue at the comfort of your home",
        ltoLogo,
        dfaLogo,
        prcLogo,
        birLogo,
        psaLogo,
        queueText: "in queue today.",
        queueNumber: null,
      };
    },
    async mounted() {
      this.checkSession();
      this.getTotalQueueNumber();
    },
    methods: {
      queue() {
        this.$router.push({ name: "schedule" }).then(() => {});
      },
      async checkSession() {
        const {
          data: { session },
          error,
        } = await supabase.auth.getSession();

        if (!session) {
          this.$router.push("login");
        } 
      },
      async getTotalQueueNumber() {
        const today = new Date(
          new Date().toLocaleString("en-US", { timeZone: "Asia/Manila" })
        );
        const currentDay = new Date(today);
        const dateString = currentDay.toLocaleDateString("en-CA");
        const { count, error} =
          await supabase
            .from("tickets")
            .select("ticket_id", { count: "exact", head: true })
            .eq("queue_date", dateString);
            
        this.queueNumber = count;
      },
      async SignOut() {
        const { error } = await supabase.auth.signOut()
        this.$router.push("login");
      }
    },
  };
</script>

<style scoped>
  .landPage {
    background: #dee2e6;
    height: 39.3rem;
  }

  h1 {
    font-weight: 800;
    padding-top: 1rem;
    padding-bottom: 2rem;
  }

  @keyframes slide {
    from {
      transform: translateX(0);
    }
    to {
      transform: translate(-100%);
    }
  }

  .logos {
    overflow: hidden;
    padding: 2.5rem;
    white-space: nowrap;
    position: relative;
  }

  .logos:before,
  .logos:after {
    position: absolute;
    top: 0;
    width: 15.625rem;
    height: 100%;
    content: "";
    z-index: 2;
  }

  .logos:before {
    left: 0;
    background: linear-gradient(to left, rgba(255, 255, 255, 0), #dee2e6);
  }

  .logos:after {
    right: 0;
    background: linear-gradient(to right, rgba(255, 255, 255, 0), #dee2e6);
  }

  .logos:hover .logosSlide {
    animation-play-state: paused;
  }

  .logosSlide {
    display: inline-block;
    animation: 25s slide infinite linear;
  }

  .logosSlide img {
    height: 18rem;
    margin: -2.5rem 0 -2.5rem 2.5rem;
  }

  .comingSoon {
    opacity: 0.5;
  }

  .queueText {
    display: flex;
    justify-content: center;
    font-size: 1.25rem;
    align-items: center;
    margin-top: 3rem;
    font-weight: 700;
  }

  .dynamic {
    color: #2252a0;
    margin-right: 0.625rem;
  }

  .btn {
    width: Fill (8.625rem);
    height: Hug 3.125rem;
    padding: 1rem 1.5rem 1rem 1.5rem;
    gap: 0.5rem;
    border: none;
    background: var(--colors-blue-blue-800, #084298);
    font-weight: 600;
    font-size: 1rem;
    display: flex;
    justify-content: center;
    align-items: center;
  }

  .btn:hover {
    color: #f0f1f5;
    background-color: #2252a0;
  }

  .queueNowButton {
    display: flex;
    justify-content: center;
    align-items: center;
    margin-top: 0.93rem;
  }
</style>
