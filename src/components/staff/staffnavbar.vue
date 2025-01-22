<template>
  <div class="navbar sticky-top">
    <nav class="navbar navbar-expand-lg navbar-light bg-transparent">
      <div class="container-fluid">
        <img
          :src="lineupLogo"
          alt=""
          @click="navigateOrScrollToLandingPage()"
          class="logo"
        />
        <button
          class="navbar-toggler"
          type="button"
          data-bs-toggle="collapse"
          data-bs-target="#navbarNavAltMarkup"
          aria-controls="navbarNavAltMarkup"
          aria-expanded="false"
          aria-label="Toggle navigation"
        >
          <span class="navbar-toggler-icon"></span>
        </button>
        <div
          class="collapse navbar-collapse justify-content-end"
          id="navbarNavAltMarkup"
        >
          <div class="navbar-nav">
            <a class="nav-link" href="staffSchedule">Schedule</a>
            <a class="nav-link" href="services">Verify Documents</a>
            <a class="nav-link" href="staffServicesInfo">Services</a>
            <img :src="logout" alt="logout" @click="signoff()" class="logout" />
          </div>
        </div>
      </div>
    </nav>
  </div>
</template>

<script>
  import lineupLogo from "@/assets/lightLogo.svg";
  import { gsap } from "gsap";
  import { ScrollToPlugin } from "gsap/ScrollToPlugin";
  import logout from "@/assets/logout.svg";
  import { supabase } from "@/client/supabase";

  gsap.registerPlugin(ScrollToPlugin);

  export default {
    name: "navBar",
    data() {
      return {
        lineupLogo,
        logout,
        windowNumber: null,
      };
    },
    mounted() {
      this.getWindowNumber();
    },
    methods: {
      async getWindowNumber() {
        const {
          data: { session },
          error,
        } = await supabase.auth.getSession();

        if (session) {
          const { data, error } = await supabase
            .from("windows")
            .select("window_number")
            .eq("email", session.user.email);
          this.windowNumber = data[0].window_number;
        }
      },
      async signoff() {
        const today = new Date(
          new Date().toLocaleString("en-US", { timeZone: "Asia/Manila" })
        );
        const hours = String(today.getHours()).padStart(2, "0");
        const minutes = String(today.getMinutes()).padStart(2, "0");
        const seconds = String(today.getSeconds()).padStart(2, "0");
        const formattedTime = `${hours}:${minutes}:${seconds}`;

        const { error } = await supabase.auth.signOut();
        const { data } = await supabase
          .from("staff_logs")
          .update({ end: formattedTime })
          .is("end", null)
          .eq("window_number", this.windowNumber);

        this.$router.push("login");
      },
      navigateOrScrollToAboutUs(sectionId) {
        const currentRoute = this.$route.name;
        if (currentRoute === "staffhome") {
          this.scrollToAboutUs(sectionId);
        } else {
          this.$router.push({ name: "staffhome" }).then(() => {
            this.$nextTick(() => {
              this.$nextTick(() => {
                this.scrollToAboutUs(sectionId);
              });
            });
          });
        }
      },
      navigateOrScrollToLandingPage() {
        this.$router.push({ name: "staffhome" }).then(() => {
          this.$nextTick(() => {
            window.scrollTo({
              top: 0,
              behavior: "smooth",
            });
          });
        });
      },
    },
  };
</script>

<style scoped>
  .navbar {
    --bs-navbar-padding-y: 0.25rem;
    width: 100%;
    height: 3.5rem;
    width: 100%;
    background: var(--colors-blue-blue-800, #052c65);
    padding-left: 1rem;
  }

  .navbar-nav {
    gap: 5rem;
    padding-right: 3rem;
  }

  .nav-link {
    font-size: 0.85rem;
    cursor: pointer;
    color: #f8f9fa;
  }

  .nav-link:hover {
    color: #c0d6e8;
  }

  .logo {
    cursor: pointer;
    height: 2.5rem;
    width: 4.375rem;
    margin-top: -0.5rem;
  }

  .logout {
    cursor: pointer;
  }
</style>
