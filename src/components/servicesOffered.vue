<template>
    <div class="servicesOffered">
        <img :src="ltoLogo" alt="ltoLogo" class="ltoLogo">
        <div class="globalHeader">
            <p>Services Offered</p>
        </div>
        <div class="boxContainer">
            <div class="servicesBox" v-for="(index) in boxes" :key="index">
                <p> Box {{ index + 1 }}</p>
            </div>
        </div>
    </div>
</template>

<script>
import ltoLogo from '@/assets/ltoLogo.svg'

export default {
    name: "servicesOffered",
    data() {
        return {
            ltoLogo,
            boxes: Array(3).fill(null)
        }
    } 
}
</script>

<style scoped>
.servicesOffered {
    display: flex;
    justify-content: center;
    align-items: center;
    flex-direction: column;
}

.ltoLogo {
    width: 100px;
    height: 100px;
    margin-top: 23px;
    margin-bottom: -120px;
}

.boxContainer {
    display: flex;
    flex-wrap: wrap;
    justify-content: center;
    gap: 30px;
    width: 100%;
}

.servicesBox {
    width: 24.9%;
    height: 306px;
    background-color: #E0E4EB;
    border: 2px solid #E0E4EB;
    display: flex;
    justify-content: center;
    align-items: center;
    box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.3);
    border-radius: 15px;
}

</style>
