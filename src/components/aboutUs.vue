<template>
    <div id="aboutUs" class="aboutUs">
        <div class="globalHeader" id="whatIs"> 
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
    padding-top: 85px;
    padding-bottom: 85px;
}

.logo {
        width: 311px;
        height: 169px; 
        margin: 0 -40px 0 -25px;
    }

.container {
    display: flex;
    flex-wrap: wrap;
    justify-content: center;
    gap: 25px;
    max-width: 1851px;
    margin-left: 20px;
}

#whatIs {
    margin-bottom: 10px;
}

.infoBox {
    width: 600.44px;
    height: 221.78px;
    background-color: #E0E4EB;
    border: 2px solid #E0E4EB;
    display: flex;
    justify-content: center;
    align-items: center;
    box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.3);
    border-radius: 15px;
}

@media (max-width: 1366px) {
    .logo {
        width: 250px;
        height: 136px;
        margin: 0 -20px 0 -15px;
    }

    .container {
        gap: 15px;
        margin-left: 10px;
        max-width: 1200px;
    }

    .infoBox {
        width: 500px;
        height: 200px;
    }
}

</style>
