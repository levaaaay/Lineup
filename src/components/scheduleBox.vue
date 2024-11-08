<template>
    <div class="scheduleBox">
        <div class="globalHeader">Schedule</div>
        <div class="container">
            <div class="box">
                <div class="container">
                    <div class="halfContainer" id="red">
                        <div class="day">Wednesday</div>
                        <div class="date">30.10</div>
                        <div class="button">Queue Now</div>
                    </div>
                    <div class="halfContainer" id="green">
                        <div class="line"></div>
                        <div class="columnContainer">
                            <div class="infoBox" v-for="(index) in boxes" :key="index">
                                <p> Box {{ index + 1 }}</p>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="invertedBox">
                <div class="container">
                    <div class="halfContainer" id="red">
                        <div class="invertedDay">Wednesday</div>
                        <div class="invertedDate">30.10</div>
                        <div class="invertedButton">Queue Now</div>
                    </div>
                    <div class="halfContainer" id="green">
                        <div class="invertedLine"></div>
                        <div class="columnContainer">
                            <div class="invertedInfoBox" v-for="(index) in boxes" :key="index">
                                <p> Box {{ index + 1 }}</p>
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
            boxes: Array(3).fill(null)
        }
    }
}
</script>

<style scoped>
.globalHeader {
    margin-top: 30px;
}

.container {
    width: 100%;
}

.box {
    width: 815px;
    height: 484px;
    background: #174082;
    border-radius: 15px;
    box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.3);
    margin-top: 30px;
}

.invertedBox {
    width: 815px;
    height: 484px;
    background: #E0E4EB;
    border-radius: 15px;
    box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.3);
    margin-top: 30px;
}

.halfContainer {
    display: flex;
    
}

#red, #green {
    height: 484px;
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
    font-size: 37.5px;
    color: #F0F1F5;
    margin-left: 70px;
    margin-top: 30px;
}

.invertedDay {
    font-size: 37.5px;
    color: #174082;
    margin-left: 70px;
    margin-top: 30px;
}

.date {
    font-size: 112.5px;
    color: #F0F1F5;
    margin-left: 70px;
    margin-top: -65px;
}

.invertedDate {
    font-size: 112.5px;
    color: #174082;
    margin-left: 70px;
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
    margin-left: 100px;
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
    margin-left: 100px;
    margin-top: -40px;
    color: #F0F1F5;
    font-weight: bold;
}

.line {
    width: 1.5px;
    height: 408px;
    background: #B6CFF7;
}

.invertedLine {
    width: 1.5px;
    height: 408px;
    background: #174082;
}

.infoBox {
    width: 271px;
    height: 128px;
    background: #B6CFF7;
    border: none;
    border-radius: 10px;
    margin-left: 70px;
}

.invertedInfoBox {
    width: 271px;
    height: 128px;
    background: #174082;
    border: none;
    border-radius: 10px;
    margin-left: 70px;
}

.columnContainer {
    display: flex;
    flex-direction: column;
    gap: 10px;
}

</style>
