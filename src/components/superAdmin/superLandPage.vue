<template>
  <div class="landPage">
    <div class="globalHeader">
      <h1 class="text-center">Welcome to</h1>
      <img :src="lineupLogo" alt="lineup" class="logo" />
      <h1>, {{ name }}!</h1>
    </div>
    <div style="display: flex; align-items: center; justify-content: center">
      <img
        :src="ltoLogo"
        alt="LTO Logo"
        style="width: 18.75rem; height: 18.75rem"
      />
    </div>
    <div class="queueText">
      <div class="dynamic">{{ queueNumber }}</div>
      <span>{{ queueText }}</span>
    </div>
    <div class="queueNowButton">
      <button class="btn btn-primary" @click="client">View Report</button>
    </div>
    <div class="queueNowButton">
      <button class="btn btn-primary" @click="admin">
        View as System Admin
      </button>
    </div>
  </div>
</template>

<script>
  import ltoLogo from "@/assets/ltoLogo.svg";
  import lineupLogo from "@/assets/lineupLogo.svg";
  import { supabase } from "@/client/supabase";

  export default {
    name: "landPage",
    data() {
      return {
        name: null,
        ltoLogo,
        lineupLogo,
        queueText: "in queue today.",
        queueNumber: null,
      };
    },
    mounted() {
      this.getTotalQueueNumber();
      this.displayName();
    },
    methods: {
      admin() {
        this.$router.push({ path: "/sysadhome" }).then(() => {});
      },
      client() {
        this.$router.push({ path: "/report" }).then(() => {});
      },
      async getTotalQueueNumber() {
        const today = new Date(
          new Date().toLocaleString("en-US", { timeZone: "Asia/Manila" })
        );
        const currentDay = new Date(today);
        const dateString = currentDay.toLocaleDateString("en-CA");
        const { count, error } = await supabase
          .from("tickets")
          .select("ticket_id", { count: "exact", head: true })
          .eq("queue_date", dateString);

        this.queueNumber = count;
      },
      async displayName() {
        const {
          data: { session },
          error,
        } = await supabase.auth.getSession();

        if (session) {
          const { data, error } = await supabase
            .from("users")
            .select("display_name")
            .eq("email", session.user.email);
          this.name = data[0].display_name;
        }
      },
    },
  };
</script>

<style scoped>
  .landPage {
    display: flex;
    flex-direction: column;
    background: #dee2e6;
  }

  h1 {
    font-weight: 800;
    padding-top: 1rem;
    padding-bottom: 2rem;
  }

  .logo {
    width: 8.3rem;
    height: 4.75rem;
    margin: -0.6rem 0.1rem 0 1rem;
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
    background: var(--colors-blue-blue-800, #031633);
    font-weight: 600;
    font-size: 1rem;
    display: flex;
    justify-content: center;
    align-items: center;
  }

  .btn:hover {
    color: #f0f1f5;
    background-color: #084298;
  }

  .queueNowButton {
    display: flex;
    justify-content: center;
    align-items: center;
    margin: 1rem;
  }
</style>
