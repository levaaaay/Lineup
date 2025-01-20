<template>
    <div class="qWithL"> 
        <div class="globalHeader">
            <h1>Queueing with </h1>
            <img :src="lineupLogo" class="logo"> 
        </div>
        <div id="carouselExampleIndicators" class="carousel slide" data-bs-ride="carousel">
            <div class="carousel-indicators">
                <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="0" class="active" aria-current="true" aria-label="Slide 1"></button>
                <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="1" aria-label="Slide 2"></button>
                <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="2" aria-label="Slide 3"></button>
                <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="3" aria-label="Slide 4"></button>
                <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="4" aria-label="Slide 5"></button>
                <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="5" aria-label="Slide 6"></button>
                <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="6" aria-label="Slide 7"></button>
                <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="7" aria-label="Slide 8"></button>
                <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="8" aria-label="Slide 9"></button>
            </div>
            <div class="carousel-inner">
                <div class="carousel-item active">
                    <img :src="caro1" class="d-block w-100" alt="...">
                </div>
                <div class="carousel-item">
                    <img :src="caro2" class="d-block w-100" alt="...">
                </div>
                <div class="carousel-item">
                    <img :src="caro3" class="d-block w-100" alt="...">
                </div>
                <div class="carousel-item">
                    <img :src="caro4" class="d-block w-100" alt="...">
                </div>
                <div class="carousel-item">
                    <img :src="caro5" class="d-block w-100" alt="...">
                </div>
                <div class="carousel-item">
                    <img :src="caro6" class="d-block w-100" alt="...">
                </div>
                <div class="carousel-item">
                    <img :src="caro7" class="d-block w-100" alt="...">
                </div>
                <div class="carousel-item">
                    <img :src="caro8" class="d-block w-100" alt="...">
                </div>
                <div class="carousel-item">
                    <img :src="caro9" class="d-block w-100" alt="...">
                </div>
            </div>
            <button class="carousel-control-prev" type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide="prev">
                <span class="carousel-control-prev-icon" aria-hidden="true"></span>
                <span class="visually-hidden">Previous</span>
            </button>
            <button class="carousel-control-next" type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide="next">
                <span class="carousel-control-next-icon" aria-hidden="true"></span>
                <span class="visually-hidden">Next</span>
            </button>
        </div>
    </div>
</template>

<script>
import lineupLogo from '@/assets/lineupLogo.svg'
import caro1 from '@/assets/caro1.svg'
import caro2 from '@/assets/caro2.svg'
import caro3 from '@/assets/caro3.svg'
import caro4 from '@/assets/caro4.svg'
import caro5 from '@/assets/caro5.svg'
import caro6 from '@/assets/caro6.svg'
import caro7 from '@/assets/caro7.svg'
import caro8 from '@/assets/caro8.svg'
import caro9 from '@/assets/caro9.svg'

export default {
    name: "qWithL",
    data() {
        return {
            lineupLogo,
            caro1,
            caro2,
            caro3,
            caro4,
            caro5,
            caro6,
            caro7,
            caro8,
            caro9,
        }
    },
};
</script>

<style scoped>
.qWithL {
    background: #DEE2E6;
    height: 39.3rem;
}

.qWithLHeader {
    display: flex;
    font-optical-sizing: auto;
    justify-content: center;
    text-align: center;
    align-items: center;
}

.logo {
    width: 8.31rem;
    height: 4.75rem; 
    margin: 3.3rem 0.5rem 0 1rem;
}

.container {
    display: flex;
    flex-wrap: wrap;
    justify-content: center;
}

.carousel {
    max-width: 69.75rem; 
    height: auto;  
    margin: 0 auto; 
}

.carousel-inner {
    height: 25rem; 
}

.carousel-item img {
    object-fit: cover; 
    width: 100%;     
    height: 100%;     
}

.carousel-indicators button {
    background-color: #666;
}

.carousel-control-prev-icon,
.carousel-control-next-icon {
    width: 2rem; 
    height: 2rem;
    background-size: 100%;
}
</style>
