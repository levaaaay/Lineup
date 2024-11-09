<template>
    <div class="scheduleBox">
        <div class="globalHeader">Schedule</div>
            <div class="boxContainer">
                <div 
                    v-for="(day, index) in twoWeeksDays"
                    :key="index"
                    :class="index % 2 === 0 ? 'box' : 'invertedBox'"
                >
                <div class="container">
                    <div class="halfContainer" id="red">
                        <div :class="index % 2 === 0 ? 'day' : 'invertedDay'">{{ day.formattedDay }}</div>
                        <div :class="index % 2 === 0 ? 'date' : 'invertedDate'">{{ day.formattedDate }}</div>
                        <div :class="index % 2 === 0 ? 'button' : 'invertedButton'">Queue Now</div>
                    </div>
                    <div class="halfContainer" id="green">
                        <div :class="index % 2 === 0 ? 'line' : 'invertedLine'"></div>
                        <div class="columnContainer">
                            <div
                                v-for="(infoBox, boxIndex) in boxes"
                                :key="boxIndex"
                                :class="index % 2 === 0 ? 'infoBox' : 'invertedInfoBox'"
                            >
                                <p> Box {{ boxIndex + 1 }}</p>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>    
</template>

<script>
export default {
    name: "scheduleBox",
    data() {
        return {
            boxes: Array(3).fill(null),
            twoWeeksDays: this.generateTwoWeeks(),
        };
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
    },
};
</script>

<style scoped>
.globalHeader {
    margin-top: 0px;
}

.boxContainer {
    width: 100%;
    display: flex;
    justify-content: center;
    align-items: center;
    gap: 100px;
    flex-wrap: nowrap;
    margin-left: 5875px;
}

.container {
    width: 100%;
    height: 100%;
}

.box, .invertedBox {
    width: 53.4%;
    min-width: 53.4%;
    height: 404px;
    background: #174082;
    border-radius: 15px;
    box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.3);
    margin-top: 10px;
    margin-left: 80px;
}

.invertedBox {
    background: #E0E4EB;
}

.halfContainer {
    display: flex;
    height: 100%;
}

#red {
    width: 50%;
    flex-direction: column;
}

#green {
    width: 50%;
    margin-left: -30px;
    display: flex;
    align-items: center;
}

.day {
    font-size: 27.5px;
    color: #F0F1F5;
    margin-left: 50px;
    margin-top: 30px;
}

.invertedDay {
    font-size: 27.5px;
    color: #174082;
    margin-left: 50px;
    margin-top: 30px;
}

.date {
    font-size: 112.5px;
    color: #F0F1F5;
    margin-left: 50px;
    margin-top: -65px;
}

.invertedDate {
    font-size: 112.5px;
    color: #174082;
    margin-left: 50px;
    margin-top: -65px;
}

.button {
    display: flex;
    justify-content: center;
    align-items: center;
    width: 235px;
    height: 65px;
    background: #B6CFF7;
    border-radius: 40px;
    margin-left: 60px;
    margin-top: -40px;
    color: #174082;
    font-weight: bold;
}

.invertedButton {
    display: flex;
    justify-content: center;
    align-items: center;
    width: 235px;
    height: 65px;
    background: #174082;
    border-radius: 40px;
    margin-left: 60px;
    margin-top: -40px;
    color: #F0F1F5;
    font-weight: bold;
}

.line {
    width: 1.5px;
    height: 330px;
    background: #B6CFF7;
}

.invertedLine {
    width: 1.5px;
    height: 330px;
    background: #174082;
}

.infoBox {
    width: 69.1%;
    height: 25.5%;
    background: #B6CFF7;
    border: none;
    border-radius: 10px;
    margin-left: 70px;
}

.invertedInfoBox {
    width: 69.1%;
    height: 25.5%;
    background: #174082;
    border: none;
    border-radius: 10px;
    margin-left: 70px;
}

.columnContainer {
    display: flex;
    flex-direction: column;
    justify-content: center;
    gap: 10px;
    width: 100%;
    height: 100%;
}

</style>
