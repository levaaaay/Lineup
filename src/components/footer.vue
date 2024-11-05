<template>
    <div class="footer">
        <div class="footerBar">
            <img :src="lineupLogo" class="footerLogo">
        </div>
    </div>
</template>

<script>
import lineupLogo from "@/assets/lineupLogo.svg"

export default {
    name: "footer",
    data() {
        return {
            lineupLogo
        }
    }
}

</script>

<style scoped>
.footerBar {
    height: 99px;
    background: #E0E4EB;
    display: flex; 
    justify-content: center;
    align-items: center; 
    border-top: 1px solid rgba(0, 0, 0, 1);
    margin-top: 38px;
}

.footerLogo {
    width: 175px;
    height: 97;
}
</style>
