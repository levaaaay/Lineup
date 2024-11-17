<template>
    <div class="servicesOffered">
        <div class="globalHeader">
            <h1>Services Offered</h1>
        </div>
        <div class="container">
            <div class="card">
                <div class="card-body">
                    <h5 class="card-title">Card title</h5>
                    <div class="line"></div>
                    <p class="card-text">Some quick example text to build on the card title and make up the bulk of the card's content.</p>
                </div>
            </div>
            <div class="card">
                <div class="card-body">
                    <h5 class="card-title">Card title</h5>
                    <div class="line"></div>
                    <p class="card-text">Some quick example text to build on the card title and make up the bulk of the card's content.</p>
                </div>
            </div>
            <div class="card">
                <div class="card-body">
                    <h5 class="card-title">Card title</h5>
                    <div class="line"></div>
                    <p class="card-text">Some quick example text to build on the card title and make up the bulk of the card's content.</p>
                </div>
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
    background: #DEE2E6;
    height: 38rem;
}

h1 {
    font-weight: 800 !important;
    padding-top: 2.43rem;
    padding-bottom: 1rem;
}

h5, p {
    color: white;
}

.ltoLogo {
    width: 100px;
    height: 100px;
    margin-top: 23px;
}

.card {
    width: 21.875rem; 
    height: 25.625rem; 
    background: #084298;
}

.line {
    width: 100%;
    height: 1.5px;
    background: #0A58CA;
}
</style>
