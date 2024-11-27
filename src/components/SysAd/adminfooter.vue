<template>
    <div class="foot">
        <div class="footerBar"></div>
    </div>
</template>

<script>

export default {
    name: "foot",
}

</script>

<style scoped>
.footerBar {
    height: 6.1875rem;
    background: #031633;
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
