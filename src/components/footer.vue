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
    height: 6.1875rem;
    background: #052C65;
    display: flex; 
    justify-content: center;
    align-items: center; 
}

@media (max-height: 768px) {
    .footerBar {
        height: 3rem;
    }
}
</style>
