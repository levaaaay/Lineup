<template>
    <div class="lineupMinds">
        <div class="invisBox">
            <div class="globalHeader">
                <h1>Minds Behind </h1>
                <img :src="lineupLogo" class="logo">
            </div>
            <div class="container">
                <div class="dev" v-for="(dev, index) in devs" :key="index">
                    <div class="minds"></div>
                    <div class="devInfo">
                        <p class="name"> {{ dev.name }} </p>
                        <p class="position"> {{ dev.position }} </p>
                    </div>
                    <div class="socIcons">
                        <img :src="gitLogo" class="git">
                        <img :src="linkedLogo" class="linked">
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import lineupLogo from '@/assets/lineupLogo.svg'
import gitLogo from '@/assets/gitLogo.svg'
import linkedLogo from '@/assets/linkedLogo.svg'

export default {
    name: "lineupMinds",
    data() {
        return {
            lineupLogo,
            gitLogo,
            linkedLogo,
            circles: Array(3).fill(null),
            devs: [
                { name: "Nicky Ronald Y. Cadalig Jr.", position: "Frontend Developer"},
                { name: "Gabriel Mark A. Capalad", position: "UI/UX Designer"},
                { name: "Peter Alvir M. Gonzales", position: "Backend Developer"}
            ]
        }
    }
}
</script>

<style scoped>
.lineupMinds {
   background: #E9ECEF;
   height: 41rem;
}

.logo {
    width: 8.31rem;
    height: 4.75rem; 
    margin: 3.3rem 0.5rem 0 1rem;
}

.container {
    display: flex;
    flex-wrap: wrap;
    justify-content: space-evenly;
}

.devContainer {
    display: flex;
    flex-direction: column;
    align-items: center;
}

.minds {
    width: 17.7475rem;
    height: 17.73rem;
    border-radius: 50%;
    background-color: #E0E4EB;
    border: 2px solid #E0E4EB;
    display: flex;
    justify-content: center;
    align-items: center;
    box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.3);
}

.devInfo {
    text-align: center;
    margin-top: 1.25rem;
}

.name {
    font-size: 1.5rem;
    font-weight: bold;
    color: #212631;
}

.socIcons {
  display: flex;
  justify-content: center;
}

.git {
    width: 3rem;
    height: 3rem;
}

.linked {
    width: 3rem;
    height: 3rem;
}
</style>
