<template>
    <div class="scheduleBox">
        <div class="globalHeader">Schedule</div>
        <div class="boxArea">
            <img class="prevButton" :src="previous" @click="goToPrevious" v-if="showPrevButton">
            <div class="boxContainer" :style="containerStyle">
                <div v-for="(day, index) in twoWeeksDays" :key="index" class="box" :class="{ current: index === currentIndex }">
                    <div class="red">
                        <div class="day">{{ day.formattedDay }}</div>
                        <div class="date">{{ day.formattedDate }}</div>
                        <div class="button" @click="queue">Queue Now</div>
                    </div>
                    <div class="green">
                        <div class="line"></div>
                    </div>
                    <div class="blue">
                        <div v-for="(infoBox, boxIndex) in boxes" :key="boxIndex" class="infoBox" @click="serviceClick(boxIndex + 1)">
                            <p>Box {{ boxIndex + 1 }}</p>
                        </div>
                    </div>
                </div>
            </div>
            <img class="nextButton" :src="next" @click="goToNext" v-if="showNextButton">
        </div>
    </div>
</template>


<script>
import previous from '@/assets/previous.svg';
import next from '@/assets/next.svg';

export default {
    name: "scheduleBox",
    data() {
        return {
            previous,
            next,
            showPrevButton: false,
            showNextButton: true,
            currentIndex: 0, 
            boxes: Array(3).fill(null),
            twoWeeksDays: this.generateTwoWeeks(),
            selectedService: ""
        };
    },
    computed: {
        containerStyle() {
            const offset = -this.currentIndex * 68; 
            return {
                transform: `translateX(${offset}vw)`,
                transition: 'transform 0.5s ease', 
            };
        }
    },
    methods: {
        generateTwoWeeks() {
            const days = [];
            const today = new Date();

            for (let i = 0; i < 14; i++) {
                const date = new Date(today);
                date.setDate(today.getDate() + i);

                const formattedDay = date.toLocaleDateString("en-US", { weekday: "long" });
                const day = String(date.getDate()).padStart(2, '0');
                const month = String(date.getMonth() + 1).padStart(2, '0');
                const formattedDate = `${month}.${day}`;

                days.push({
                    formattedDay,
                    formattedDate,
                    date,
                });
            }
            return days;
        },
        goToNext() {
            if (this.currentIndex < this.twoWeeksDays.length - 1) {
                this.currentIndex++;
                this.showPrevButton = true;
            } else if (this.currentIndex == this.twoWeeksDays.length - 1) {
                this.showNextButton = false;
            }
        },
        goToPrevious() {
            if (this.currentIndex > 0 && this.currentIndex == 1) {
                this.currentIndex--;
                this.showNextButton = true; 
                this.showPrevButton = false;
            } else if (this.currentIndex > 0) {
                this.currentIndex--;
                this.showNextButton = true; 
            }
        },
        queue() {
            alert(`Queued for ${this.selectedService}`);
        },
        serviceClick(boxNumber) {
            if (boxNumber == 1) {
                this.selectedService = "drivers license";
            } else if (boxNumber == 2) {
                this.selectedService = "OR";
            } else if (boxNumber == 3) {
                this.selectedService = "Random Shit";
            }
            alert(this.selectedService);
        }
    }
};
</script>

<style scoped>
.globalHeader {
    margin-top: 0px;
}

.boxArea {
    width: 100%;
    display: flex;
    justify-content: center;
    align-items: center;
    position: relative;
}

.prevButton, .nextButton {
    width: 3vw;
    height: 3vw;
    position: absolute;
    top: 50%;
    transform: translateY(-50%);
    z-index: 10;
    cursor: pointer;
}

.prevButton {
    left: 15vw;
}

.nextButton {
    right: 15vw;
}

.boxContainer {
    display: flex;
    justify-content: center;
    align-items: center;
    flex-wrap: nowrap;
    margin-left: 883vw;
    gap: 18vw;
}

.box {
    width: 50vw;
    background: #174082;
    border-radius: 15px;
    box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.3);
    display: flex;
    padding: 2.5vw 0 2.5vw 0;
    flex-shrink: 0;
    transition: transform 0.5s ease; 
}

.red {
    width: 45%;
    display: flex;
    flex-direction: column;
    padding-left: 1.5vw;
}

.green {
    display: flex;
    align-items: center;
}

.blue {
    display: flex;
    flex-direction: column;
    justify-content: center;
    gap: 20px;
}

.day, .invertedDay {
    font-size: 2.5em;
    color: #F0F1F5;
    margin-left: 2.3vw;
}

.invertedDay {
    color: #174082;
}

.date, .invertedDate {
    font-size: 7em;
    color: #F0F1F5;
    margin-left: 2.2vw;
    margin-top: -3vw;
}

.invertedDate {
    color: #174082;
}

.button {
    display: flex;
    justify-content: center;
    align-items: center;
    width: 14vw;
    height: 3.5vw;
    background: #B6CFF7;
    border-radius: 40px;
    margin-left: 3vw;
    margin-top: -2vw;
    color: #174082;
    font-weight: bold;
    cursor: pointer;
}

.line, .invertedLine {
    width: 0.1vw;
    height: 27vw;
    background: #B6CFF7;
    margin-left: 3.2vw;
}

.invertedLine {
    background: #174082;
}

.infoBox, .invertedInfoBox {
    width: 20vw;
    height: 8vw;
    background: #B6CFF7;
    border: none;
    border-radius: 10px;
    margin-left: 2vw;
    cursor: pointer;
}

.invertedInfoBox {
    background: #174082;
}
</style>
