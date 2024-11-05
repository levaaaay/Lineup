<template>
    <div class="qWithL"> 
        <div class="globalHeader">
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
.qWithLHeader {
    display: flex;
    color: #212631;
    font-optical-sizing: auto;
    font-size: 70px;
    justify-content: center;
    text-align: center;
    font-weight: 700;
    margin-top: 120px;
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
</style>
