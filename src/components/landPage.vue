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
            this.$router.push({ name: 'schedule' }).then(() => {
            });
        },
    }
}
</script>

<style scoped>
.landPage {
    background: grey;
    height: 557px;
}
.landPageHeader {
    color: #212631;
    font-optical-sizing: auto;
    font-size: 55px;
    justify-content: center;
    text-align: center;
    font-weight: 800;
    margin-top: 0px;
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
    height: 205px;
    margin: -40px 0 -50px 40px;
}

.comingSoon {
    opacity: 0.5;
}

.queueText {
    display: flex;
    justify-content: center;
    font-size: 25px;    
    align-items: center;
    margin-top: 20px;
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
    padding: 7px 60px;
    border: 2px solid #174082;
    border-radius: 30px;
    cursor: pointer;
    margin-top: 10px;
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
</style>
