<template>
    <div class="footer">
        <div class="footerBar">
            <img :src="lineupLogo" class="footerLogo">
        </div>
    </div>
</template>

<script>

export default {
    name: "footer",
}

</script>

<style scoped>
.footerBar {
    height: 99px;
    background: #052C65;
    display: flex; 
    justify-content: center;
    align-items: center; 
}
</style>
