<template>
    <div class="navbar sticky-top">
        <nav class="navbar navbar-expand-lg navbar-light bg-transparent">
            <div class="container-fluid">
                <img :src="lineupLogo" alt="" @click="navigateOrScrollToLandingPage()" class="logo">
                <button class="navbar-toggler" type="button" data-bs-toggle="collapse"
                    data-bs-target="#navbarNavAltMarkup" aria-controls="navbarNavAltMarkup" aria-expanded="false"
                    aria-label="Toggle navigation">
                    <span class="navbar-toggler-icon"></span>
                </button>
                <div class="collapse navbar-collapse justify-content-end" id="navbarNavAltMarkup">
                    <div class="navbar-nav">
                        <a class="nav-link" @click="navigateOrScrollToAboutUs('aboutUs')">About Us</a>
                        <a class="nav-link" href="schedule">Schedule</a>
                        <a class="nav-link" href="ticket">Ticket</a>
                        <img :src="logout" alt="logout" @click="logout" class="logout">
                    </div>
                </div>
            </div>
        </nav>
    </div>
</template>

<script>
import lineupLogo from '@/assets/lightLogo.svg';
import { gsap } from "gsap";
import { ScrollToPlugin } from "gsap/ScrollToPlugin";
import logout from "@/assets/logout.svg";
import { supabase } from "../client/supabase";

gsap.registerPlugin(ScrollToPlugin);

export default {
    name: "navBar",
    data() {
        return {
            lineupLogo,
            logout,
        }
    },
    methods: {
        scrollToAboutUs(sectionId) {
            const section = document.getElementById(sectionId);
            if (section) {
                const offset = 0;
                const elementPosition = section.getBoundingClientRect().top + window.scrollY;
                window.scrollTo({
                    top: elementPosition + offset,
                    behavior: "smooth"
                });
            };
        },
       async logout() {
            const { error } = await supabase.auth.signOut()
            this.$router.push("login");
        },
    },

    navigateOrScrollToAboutUs(sectionId) {
        const currentRoute = this.$route.name;
        if (currentRoute === 'home') {
            this.scrollToAboutUs(sectionId);
        } else {
            this.$router.push({ name: 'home' }).then(() => {
                this.$nextTick(() => {
                    this.$nextTick(() => {
                        this.scrollToAboutUs(sectionId);
                    });
                });
            });
        }
    },

    navigateOrScrollToLandingPage() {
        this.$router.push({ name: 'home' }).then(() => {
            this.$nextTick(() => {
                window.scrollTo({
                    top: 0,
                    behavior: "smooth"
                });
            });
        });
    },
}
</script>

<style scoped>
.navbar {
    --bs-navbar-padding-y: 0.25rem;
    width: 100%;
    height: 3.5rem;
    width: 100%;
    background: var(--colors-blue-blue-800, #084298);
    padding-left: 1rem;
}

.navbar-nav {
    gap: 5rem;
    padding-right: 3rem;
}

.nav-link {
    font-size: 0.85rem;
    cursor: pointer;
    color: #F8F9FA;
}

.nav-link:hover {
    color: #C0D6E8;
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
