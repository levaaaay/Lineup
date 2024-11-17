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
            </div>
            <div class="carousel-inner">
                <div class="carousel-item active">
                    <img :src="img1" class="d-block w-100" alt="...">
                </div>
                <div class="carousel-item">
                    <img :src="img1" class="d-block w-100" alt="...">
                </div>
                <div class="carousel-item">
                    <img :src="img1" class="d-block w-100" alt="...">
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
import img1 from '@/assets/crossimg.svg'

export default {
    name: "qWithL",
    data() {
        return {
            lineupLogo,
            img1
        }
    }
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
