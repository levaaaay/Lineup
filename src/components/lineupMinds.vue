<template>
    <div class="lineupMinds">
        <div class="invisBox">
            <div class="globalHeader">
                <p>Minds Behind </p>
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
.logo {
    width: 291px;
    height: 132px; 
    margin: 0 -40px 0 -25px;
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
    width: 283.96px;
    height: 283.71px;
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
    margin-top: 20px;
}

.name {
    font-size: 24px;
    font-weight: bold;
    color: #212631;
}

.socIcons {
  display: flex;
  justify-content: center;
}

.git {
    width: 48px;
    height: 48px;
}

.linked {
    width: 48px;
    height: 48px;
}

</style>
