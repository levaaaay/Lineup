<template>
    <div id="aboutUs" class="aboutUs">
        <div class="invisBox">
            <div class="globalHeader"> 
                <p> What is </p>
                <img :src="lineupLogo" alt="lineuplogo" class="logo"> 
                <p>?</p>
            </div>
            <div class="container">
                <div class="infoBox" v-for="(index) in boxes" :key="index">
                    <p> Box {{ index + 1 }}</p>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import lineupLogo from '@/assets/lineupLogo.svg';

export default {
    name: "aboutUs",
    data() {
        return {
        lineupLogo,
        boxes: Array(4).fill(null)
        }
    }
}
</script>

<style Scoped>
.aboutUs {
    padding-top: 50px;
    margin-top: -50px;
}

.invisBox {
    background: grey;
    height: 557px;
}

.logo {
        width: 291px;
        height: 149px; 
        margin: 0 -40px 0 -25px;
    }

.container {
    display: flex;
    flex-wrap: wrap;
    justify-content: center;
    gap: 30px;
}

.infoBox {
    width: 550.44px;
    height: 171.78px;
    background-color: #E0E4EB;
    border: 2px solid #E0E4EB;
    display: flex;
    justify-content: center;
    align-items: center;
    box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.3);
    border-radius: 15px;
}
</style>
