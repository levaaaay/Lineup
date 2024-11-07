<template>
    <div class="qWithL"> 
        <div class="qWithLHeader">
            <p>Queueing with </p>
            <img :src="lineupLogo" class="logo"> 
        </div>
        <div class="container">
            <div class="box">
                <p> box 1</p>
            </div>
        </div>
    </div>
</template>

<script>
import lineupLogo from '@/assets/lineupLogo.svg'

export default {
    name: "qWithL",
    data() {
        return {
            lineupLogo
        }
    }
};
</script>

<style scoped>
.qWithL {
    padding: 85px 0 85px 0;
}

.qWithLHeader {
    display: flex;
    color: #212631;
    font-optical-sizing: auto;
    font-size: 70px;
    justify-content: center;
    text-align: center;
    font-weight: 700;
    align-items: center;
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
}

.box {
    display: flex;
    justify-content: center;
    width: 1235px;
    height: 469px;
    background-color: #E0E4EB;
    border: 2px solid #E0E4EB;
    align-items: center;
    box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.3);
    border-radius: 15px;
}

@media (max-width: 1366px) {
    .qWithL {
        padding: 70px 0;
    }

    .qWithLHeader {
        font-size: 50px;
    }

    .logo {
        width: 250px;
        height: 136px;
        margin: 0 -20px 0 -15px;
    }

    .box {
        width: 1000px;
        height: 400px;
    }
}
</style>
