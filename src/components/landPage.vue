<template>
    <div class="landPage">
        <div class="landPageHeader">
            <p class="headerline">{{ headerLine1 }}</p>
            <p class="headerline2">{{ headerLine2 }}</p>
        </div>
        <div class="logos">
            <div class="logosSlide">
                <img class="comingSoon" :src="prcLogo" alt="PRC Logo">
                <img class="comingSoon" :src="dfaLogo" alt="DFA Logo">
                <img :src="ltoLogo" alt="LTO Logo">
                <img class="comingSoon" :src="birLogo" alt="BIR Logo">
                <img class="comingSoon" :src="psaLogo" alt="PSA Logo">
            </div>
            <div class="logosSlide">
                <img class="comingSoon" :src="prcLogo" alt="PRC Logo">
                <img class="comingSoon" :src="dfaLogo" alt="DFA Logo">
                <img :src="ltoLogo" alt="LTO Logo">
                <img class="comingSoon" :src="birLogo" alt="BIR Logo">
                <img class="comingSoon" :src="psaLogo" alt="PSA Logo">
            </div>
        </div>
        <div class="queueText">
            <div class="dynamic">{{ queueNumber }}</div>
            <span>{{ queueText }}</span>
        </div>
        <div class="queueNowButton">
            <button @click="queue">Queue Now</button>
        </div>
    </div>
</template>

<script>
import ltoLogo from '@/assets/ltoLogo.svg'
import dfaLogo from '@/assets/dfaLogo.svg'
import prcLogo from '@/assets/prcLogo.svg'
import birLogo from '@/assets/birLogo.svg'
import psaLogo from '@/assets/psaLogo.svg'

export default {
    name: "landPage",
    data() {
        return {
            headerLine1: "Queue at the Comfort",
            headerLine2: "of Your Home",
            ltoLogo,
            dfaLogo,
            prcLogo,
            birLogo,
            psaLogo,
            queueText: "In Queue Today.",
            queueNumber: 200
        }
    },
    methods: {
        queue() {
            alert("TANGINAMO");
        }
    }
}
</script>

<style scoped>
.landPage {
    padding-bottom: 85px;
}

.landPageHeader {
    color: #212631;
    font-optical-sizing: auto;
    font-size: 70px;
    justify-content: center;
    text-align: center;
    font-weight: 800;
}

.headerline2 {
    margin-top: -30px;
}

@keyframes slide {
    from {
        transform: translateX(0)
    }
    to {
        transform: translate(-100%);
    }
}

.logos {
    overflow: hidden;
    padding: 40px;
    white-space: nowrap;
    position: relative;
}

.logos:before,
.logos:after {
    position: absolute;
    top: 0;
    width: 250px;
    height: 100%;
    content: "";
    z-index: 2;
}

.logos:before {
    left: 0;
    background: linear-gradient(to left, rgba(255,255,255, 0), #F0F1F5);    
}

.logos:after {
    right: 0;
    background: linear-gradient(to right, rgba(255,255,255, 0), #F0F1F5);
}

.logos:hover .logosSlide {
    animation-play-state: paused;
}

.logosSlide {
    display: inline-block;
    animation: 25s slide infinite linear;
}

.logosSlide img {
    height: 275px;
    margin: -30px 0 -40px 40px;
}

.comingSoon {
    opacity: 0.5;
}

.queueText {
    display: flex;
    justify-content: center;
    font-size: 30px;    
    align-items: center;
    margin-top: 30px;
}

.dynamic {
    color: #2252A0;
    margin-right: 10px;
}

button {
    font-size: 20px;
    font-weight: 700;
    color: #F0F1F5;
    background-color: #174082;
    padding: 10px 80px;
    border: 2px solid #174082;
    border-radius: 30px;
    cursor: pointer;
    margin-top: 30px;
}

button:hover {
    color: #F0F1F5;
    background-color: #2252A0;
    border: 2px solid #2252A0;
}

.queueNowButton {
    display: flex;
    justify-content: center;
    align-items: center;
}

@media (max-width: 1366px) {
        .navbar {
            height: 45px;
        }
        
        .logo {
            width: 90px;
            height: 45px;
            margin-left: 30px;
        }

        .navButtons {
            margin-right: 60px;
            font-size: 9px;
        }

        .navButtons p, .nav-item {
            margin-left: 30px;
            font-size: 9px;
        }
    }
</style>
