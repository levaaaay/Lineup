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
    width: 4.375rem;
    height: 2.5rem;
    margin: 0.5rem 0 0 1rem;
}
</style>
