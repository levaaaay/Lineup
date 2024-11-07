<template> 
    <div class="navbar">
        <router-link :to="{ name: 'home'}" @click="navigateOrScrollToLandingPage"><img :src="lineupLogo" alt="lineuplogo" class="logo"></router-link>
        <div class="navButtons">
            <p @click="navigateOrScrollToAboutUs('aboutUs')">{{ aboutUs }}</p>
            <router-link class="nav-item" :to="{ name: 'services'}">{{ services }}</router-link>
            <p>{{ schedule }}</p>
            <router-link class="nav-item" :to="{ name: 'login'}">{{ ticket }}</router-link>
        </div>
    </div> 
</template>

<script> 
import lineupLogo from '@/assets/lineupLogo.svg';
import { gsap } from "gsap";
import { ScrollToPlugin } from "gsap/ScrollToPlugin";

gsap.registerPlugin(ScrollToPlugin);

    export default {
        name: "navBar",
        data() {
            return {
                lineupLogo,
                aboutUs: "About Us",
                services: "Services",
                schedule: "Schedule",
                ticket: "My Ticket",
            }
        },
        methods: {
            scrollToAboutUs(sectionId) {
                const section = document.getElementById(sectionId);
                if (section) {
                    const elementPosition = section.getBoundingClientRect().top + window.scrollY;
                    window.scrollTo({
                        top: elementPosition,
                        behavior: "smooth"
                    });
                }
            },

            navigateOrScrollToAboutUs(sectionId) {
                const currentRoute = this.$route.name; 
                if (currentRoute === 'home') {
                    this.scrollToAboutUs(sectionId);
                } else {
                    this.$router.push({ name: 'home' }).then(() => {
                        this.$nextTick(() => {
                            this.scrollToAboutUs(sectionId);
                        });
                    });
                }
            },

            navigateOrScrollToLandingPage() {
                this.$router.push({ name: 'home' }).then(() => {
                    this.$nextTick(() => {
                        window.scrollTo({
                            top: 0,
                            behavior: 'smooth'
                        });
                    });
                });
            },
        }
    };
</script>

<style scoped> 
    .navbar {
        height: 50px;
        background: #F0F1F5;
        display: flex; 
        justify-content: space-between;
        align-items: center; 
        box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.2);
        border-bottom: 1px solid rgba(0, 0, 0, 0.1);
        position: sticky;
        top: 0;
        z-index: 1000;
        width: 100%;
    }

    .logo {
        width: 113px;
        height: 50px; 
        margin-left: 50px;
        cursor: pointer;
        position: relative;
        z-index: 10;
        pointer-events: auto;
    }

    .navButtons {
        color: #212631;
        display: flex;
        margin-right: 120px;
        font-size: 10px;
        font-style: normal;
        cursor: pointer;
    }

    .navButtons p, .nav-item {
        margin-top: 15px;
        margin-left: 51px;
        color: #212631;
        text-decoration: none;
    }

    .nav-item {
        cursor: pointer;
    }

    @media (max-width: 768px) {
    .navbar {
        flex-direction: column;
        height: auto;
        padding: 10px 20px;
    }

    .logo {
        margin: 0 auto;
        width: 90px;
        height: auto;
    }

    .navButtons {
        flex-direction: column;
        font-size: 12px;
    }

    .navButtons p, .nav-item {
        margin: 10px 0;
    }
}

</style>
