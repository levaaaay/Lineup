<template>
    <div id="aboutUs" class="aboutUs">
        <div class="globalHeader"> 
            <h1> What is </h1>
            <img :src="lineupLogo" alt="lineuplogo" class="logo"> 
            <h1>?</h1>
        </div>
        <div class="container">
            <div class="card" style="width: 22.75rem; height: 25.6rem;">
                <img :src="img1" class="card-img-top" alt="img1">
                <div class="card-body">
                    <h5>Two-Way Queuing System</h5>
                    <p>This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.</p>
                </div>
            </div>
            <div class="card" style="width: 22.75rem; height: 25.6rem;">
                <img :src="img2" class="card-img-top" alt="img1">
                <div class="card-body">
                    <h5>ESP32-Based Device</h5>
                    <p>This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.</p>
                </div>
            </div>
            <div class="card" style="width: 22.75rem; height: 25.6rem;">
                <img :src="img3" class="card-img-top" alt="img1">
                <div class="card-body">
                    <h5>Cross-Platform Web Application</h5>
                    <p>This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.</p>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import lineupLogo from '@/assets/lineupLogo.svg';
import img1 from '@/assets/queueimg.svg';
import img2 from '@/assets/espimg.svg';
import img3 from '@/assets/crossimg.svg';

export default {
    name: "aboutUs",
    data() {
        return {
        lineupLogo,
        img1,
        img2,
        img3,
        boxes: Array(4).fill(null)
        }
    }
}
</script>

<style Scoped>
.aboutUs {
    background: #E9ECEF;
    height: 39.3rem;
}

h1 {
    font-weight: 800 !important;
    padding-top: 5rem;
    padding-bottom: 2rem;
}

h5 {
    font-weight: 600;
}

p {
    font-size: 1rem;
    font-weight: 400;
    text-align: left;
    color: #68717A;
    padding-top: 0.5rem
}

.logo {
        width: 8.3rem;
        height: 4.75rem; 
        margin: 3.3rem 0.5rem 0 1rem;
    }

.container {
    display: flex;
    flex-wrap: nowrap;
    justify-content: center;
    align-items: center;
    gap: 1.875rem;
}
</style>
