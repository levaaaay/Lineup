<template>
    <div class="loginBackground">
        <img :src="lightLogo" class="logo">
    </div>   
</template>

<script>
import lightLogo from '@/assets/lightLogo.svg'
export default {
    name: "loginBackground",
    data() {
        return {
            lightLogo,
        }
    }
}
</script>

<style scoped>
.loginBackground {
    width: 100vw; 
    height: 100vh; 
    position: fixed;
    top: 0;
    left: 0;
    z-index: -1; 
    background: linear-gradient(#2252A0, #B6CFF7, #F0F1F5);
}

.logo {
    width: 142px;
    height: 79px;
    margin-left: 65px;
}

@media (max-width: 1366px) {
    .logo {
        width: 120px;
        height: 67px; 
        margin-left: 50px; 
    }
}
</style>
