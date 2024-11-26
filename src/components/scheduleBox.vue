<template>
    <div class="scheduleBox">
        <div class="globalHeader">
            <h1>Schedule</h1>
        </div>
        <div class="boxArea">
            <img class="prevButton" :src="previous" @click="goToPrevious" v-if="showPrevButton" />
            <div class="boxContainer" :style="containerStyle">
                <div v-for="(day, index) in twoWeeksDays" :key="index" class="card-group"
                    :class="{ current: index === currentIndex }">
                    <div class="card mb-3" style="max-width: 53.625rem; height: 22.75rem;">
                        <div class="row g-0">
                            <div class="col-md-6">
                                <div class="dateCardContent" :class="{ 'disabled-card': !selectedServiceType }">
                                    <div class="dateTime">
                                        <h3 class="card-title" :class="{ smallerFont: isCurrentCard }">
                                            {{ day.formattedDay }}
                                        </h3>
                                        <h2 class="card-title">{{ day.formattedDate }}</h2>
                                    </div>
                                    <button class="btn btn-primary" type="submit" :disabled="!selectedServiceType"
                                        :class="{ 'disabled-btn': !selectedServiceType }">
                                        Queue now
                                    </button>
                                </div>
                                <span class="backToToday" @click="resetToToday">Back to today</span>
                            </div>
                            <div class="col-md-1">
                                <div class="line"></div>
                            </div>
                            <div class="col-md-5">
                                <div class="card-body">
                                    <button class="btn btn-primary specServ"
                                        :class="{ selected: selectedServiceType === 'license' && selectedServiceIndex === index, disabled: day.license >= 100 }"
                                        :disabled="day.license >= 100" @click="selectService('license', index)">
                                        <span>Licensing</span>
                                        <span class="counter" :class="queueNumberColor(day.license)">
                                            {{ day.license }}/100
                                        </span>
                                        <span class="select">Select</span>
                                    </button>
                                    <button class="btn btn-primary specServ"
                                        :class="{ selected: selectedServiceType === 'registration' && selectedServiceIndex === index, disabled: day.registration >= 100 }"
                                        :disabled="day.registration >= 100"
                                        @click="selectService('registration', index)">
                                        <span>Registration</span>
                                        <span class="counter" :class="queueNumberColor(day.registration)">
                                            {{ day.registration }}/100
                                        </span>
                                        <span class="select">Select</span>
                                    </button>
                                    <button class="btn btn-primary specServ"
                                        :class="{ selected: selectedServiceType === 'LETAS' && selectedServiceIndex === index, disabled: day.LETAS >= 100 }"
                                        :disabled="day.LETAS >= 100" @click="selectService('LETAS', index)">
                                        <span>LETAS</span>
                                        <span class="counter" :class="queueNumberColor(day.LETAS)">
                                            {{ day.LETAS }}/100
                                        </span>
                                        <span class="select">Select</span>
                                    </button>
                                </div>


                            </div>
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
            license: 1,
            Registration: 75,
            LETAS: 50,
            previous,
            next,
            currentIndex: 0,
            twoWeeksDays: this.generateTwoWeeks(),
            selectedServiceIndex: null,
            selectedServiceType: null,
        };
    },
    computed: {
        containerStyle() {
            const offset = -this.currentIndex * 100;
            return {
                transform: `translateX(${offset}%)`,
                transition: "transform 0.5s ease-in-out",
            };
        },
        showPrevButton() {
            return this.currentIndex > 0;
        },
        showNextButton() {
            return this.currentIndex < this.twoWeeksDays.length - 1;
        },
    },
    methods: {
        generateTwoWeeks() {
            const days = [];
            const today = new Date();

            for (let i = 0; i < 14; i++) {
                const date = new Date(today);
                date.setDate(today.getDate() + i);

                const formattedDay = date.toLocaleDateString("en-US", { weekday: "long" });
                const day = String(date.getDate()).padStart(2, "0");
                const month = String(date.getMonth() + 1).padStart(2, "0");
                const formattedDate = `${month}.${day}`;

                days.push({
                    formattedDay,
                    formattedDate,
                    date,
                    license: Math.floor(Math.random() * 101),
                    registration: Math.floor(Math.random() * 101),
                    LETAS: Math.floor(Math.random() * 101),
                });
            }
            return days;
        },
        goToNext() {
            if (this.currentIndex < this.twoWeeksDays.length - 1) {
                this.currentIndex++;
            }
        },
        goToPrevious() {
            if (this.currentIndex > 0) {
                this.currentIndex--;
            }
        },
        queueNumberColor(value) {
            if (value > 76) return "red";
            if (value > 50) return "yellow";
            return "green";
        },
        resetToToday() {
            const today = new Date();
            const todayIndex = this.twoWeeksDays.findIndex(day =>
                day.date.toDateString() === today.toDateString()
            );
            if (todayIndex !== -1) {
                this.currentIndex = todayIndex;
            }
        },
        selectService(service, index) {
            const selectedDay = this.twoWeeksDays[index];
            if (this.selectedServiceType === service && this.selectedServiceIndex === index) {
                this.selectedServiceType = null;
                this.selectedServiceIndex = null;
                console.log(`Deselected ${service} on ${selectedDay.formattedDate}`);
            } else if (selectedDay[service] < 100) {
                this.selectedServiceType = service;
                this.selectedServiceIndex = index;
                console.log(`Selected ${service} on ${selectedDay.formattedDate}`);
            } else {
                console.log(`${service} is full and cannot be selected.`);
            }
        }
    },
};
</script>

<style scoped>
.scheduleBox {
    background: #dee2e6;
}

.boxArea {
    width: 100%;
    display: flex;
    justify-content: center;
    align-items: center;
    position: relative;
    overflow: hidden;
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

.boxContainer {
    display: flex;
    flex-wrap: nowrap;
    transition: transform 0.5s ease-in-out;
    width: 100%;
}

.card-group {
    min-width: 100%;
    display: flex;
    justify-content: center;
    align-items: center;
}

.row {
    display: flex;
    height: 100%;
    padding: 2rem 1.5rem 2rem 1.5rem;
    flex-wrap: nowrap;
    flex-shrink: 0;
    transition: transform 0.5s ease;
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

.disabled-card {
    opacity: 0.5;
    pointer-events: none;
}

.disabled-btn {
    background-color: #ccc;
    cursor: not-allowed;
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

.selected {
    background-color: #007bff;
    box-shadow: 3px 3px 3px rgba(0, 0, 0, 0.1);
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
    position: absolute;
    top: 50%;
    transform: translateY(-50%);
    cursor: pointer;
    width: 2rem;
    height: 2rem;
    z-index: 10;
}

.prevButton {
    left: 10rem;
}

.nextButton {
    right: 10rem;
}

.smallerFont {
    font-size: 2rem;
}
</style>
