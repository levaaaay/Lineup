<template>
    <div class="scheduleBox">
        <div class="globalHeader">
            <h1>Schedule</h1>
        </div>
        <div class="card-group">
            <img class="prevButton" :src="previous" @click="goToPrevious" v-if="showPrevButton" />
            <div class="card mb-3" style="max-width: 53.625rem; height: 22.75rem;">
                <div class="row g-0">
                    <div class="col-md-6">
                        <div class="dateCardContent">
                            <div class="dateTime">
                                <h3 class="card-title" :class="{ smallerFont: isCurrentCard }">
                                    {{ currentDay.formattedDay }}
                                </h3>
                                <h2 class="card-title">{{ currentDay.formattedDate }}</h2>
                            </div>
                            <button class="btn btn-primary" type="submit">
                                Queue now
                            </button>
                        </div>
                        <span class="backToToday">Back to today</span>
                    </div>
                    <div class="col-md-1">
                        <div class="line"></div>
                    </div>
                    <div class="col-md-5">
                        <div class="card-body">
                            <button class="specServ">
                                <span>Licensing</span>
                                <span class="counter" :class="queueNumberColor(license)">
                                    {{ license }}/100
                                </span>
                                <span class="select">Select</span>
                            </button>
                            <button class="specServ">
                                <span>Registration</span>
                                <span class="counter" :class="queueNumberColor(Registration)">
                                    {{ Registration }}/100
                                </span>
                                <span class="select">Select</span>
                            </button>
                            <button class="specServ">
                                <span>LETAS</span>
                                <span class="counter" :class="queueNumberColor(LETAS)">
                                    {{ LETAS }}/100
                                </span>
                                <span class="select">Select</span>
                            </button>
                        </div>
                    </div>
                </div>
            </div>
            <img class="nextButton" :src="next" @click="goToNext" v-if="showNextButton" />
        </div>
    </div>
</template>

<script>
import previous from "@/assets/previous.svg";
import next from "@/assets/next.svg";

export default {
    name: "scheduleBox",
    data() {
        return {
            license: 100,
            Registration: 75,
            LETAS: 50,
            previous,
            next,
            showPrevButton: false,
            showNextButton: true,
            currentIndex: 0,
            twoWeeksDays: this.generateTwoWeeks(),
        };
    },
    computed: {
        currentDay() {
            return this.twoWeeksDays[this.currentIndex];
        },
    },
    methods: {
        generateTwoWeeks() {
            const days = [];
            const today = new Date();

            for (let i = 0; i < 14; i++) {
                const date = new Date(today);
                date.setDate(today.getDate() + i);

                const formattedDay = date.toLocaleDateString("en-US", {
                    weekday: "long",
                });
                const day = String(date.getDate()).padStart(2, "0");
                const month = String(date.getMonth() + 1).padStart(2, "0");
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
            }
            if (this.currentIndex === this.twoWeeksDays.length - 1) {
                this.showNextButton = false;
            }
        },
        goToPrevious() {
            if (this.currentIndex > 0) {
                this.currentIndex--;
                this.showNextButton = true;
            }
            if (this.currentIndex === 0) {
                this.showPrevButton = false;
            }
        },
        queueNumberColor(value) {
            if (value > 76) {
                return "red";
            } else if (value > 50) {
                return "yellow";
            } else {
                return "green";
            }
        },
    },
    computed: {
            currentDay() {
                return this.twoWeeksDays[this.currentIndex];
            },
            isCurrentCard() {
                const today = new Date();
                return (
                    today.toLocaleDateString("en-US", { weekday: "long" }) ===
                    this.currentDay.formattedDay
                );
            },
        },
};
</script>

<style scoped>
.scheduleBox {
    background: #dee2e6;
}

h1 {
    font-weight: 800 !important;
    padding-top: 2.43rem;
    padding-bottom: 1rem;
}

h3 {
    font-size: 1.7rem;
}

h2 {
    font-size: 2.5rem;
}

h2,
h3 {
    font-weight: bold;
}

.card-group {
    justify-content: center;
    align-items: center;
    position: relative;
}

.row {
    height: 100%;
    padding: 2rem 1.5rem 2rem 1.5rem;
}

.dateCardContent {
    display: flex;
    align-items: center;
    justify-content: space-between;
    width: 88%;
    height: 60%;
    border: 1px solid #dee2e6;
    border-radius: 1rem;
    padding: 2rem;
}

.dateTime {
    display: flex;
    flex-direction: column;
}

.card-title {
    margin: 0;
}

.col-md-1 {
    width: 2.2rem;
}

.col-md-6 {
    display: flex;
    flex-direction: column;
    justify-content: space-between;
    height: 100%;
    position: relative;
}

.line {
    width: 1px;
    height: 98%;
    background: black;
}

.btn {
    background-color: #052c65;
    border: none;
    width: 8.625rem;
    height: 3.125rem;
}

.backToToday {
    color: #68717a;
    text-decoration: underline;
    cursor: pointer;
    margin-top: auto;
    text-align: center;
}

.specServ {
    display: flex;
    align-items: center;
    background-color: #6ea8fe;
    width: 20.625rem;
    height: 5.125rem;
    margin-bottom: 0.7rem;
    border-radius: 1rem;
    border: none;
    box-shadow: 3px 3px 3px rgba(0, 0, 0, 0.1);
    font-size: 1.75rem;
    font-weight: bold;
    padding-left: 1.7rem;
    padding-right: 1rem;
}

.counter {
    display: flex;
    align-items: center;
    justify-content: center;
    width: 3.5625rem;
    height: 1.25rem;
    background-color: #ebe5fc;
    margin-left: 0.3rem;
    border-radius: 1rem;
    font-size: 0.625rem;
}

.select {
    display: flex;
    font-size: 0.75rem;
    color: #68717a;
    font-weight: lighter;
    margin-left: auto;
    text-decoration: underline;
}

.red {
    color: #dc3545;
}

.yellow {
    color: #fd7e14;
}

.green {
    color: #198754;
}

.prevButton,
.nextButton {
    width: 30rem;
    height: 2rem;
    cursor: pointer;
    position: absolute;
    top: 50%;
    transform: translateY(-50%);
}

.prevButton {
    left: -2.5rem;
}

.nextButton {
    right: -2.5rem;
}

.smallerFont {
    font-size: 2rem; 
}

</style>
