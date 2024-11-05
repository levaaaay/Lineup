<template>
    <div class="servicesOffered">
        <img :src="ltoLogo" alt="ltoLogo" class="ltoLogo">
        <div class="globalHeader">
            <p>Services Offered</p>
        </div>
        <div class="container">
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
    width: 119px;
    height: 119px;
    margin-top: 23px;
    margin-bottom: -120px;
}

.container {
    display: flex;
    flex-wrap: wrap;
    justify-content: center;
    gap: 30px;
}

.servicesBox {
    width: 393px;
    height: 376px;
    background-color: #174082;
    border: 2px solid #174082;
    display: flex;
    justify-content: center;
    align-items: center;
    box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.3);
    border-radius: 15px;
}

</style>
