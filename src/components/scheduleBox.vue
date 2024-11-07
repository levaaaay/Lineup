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

                    </div>
                </div>
            </div>
        </div>
    </div>    
</template>

<script>
export default {
    name: "scheduleBox",
}
</script>

<style scoped>
.globalHeader {
    margin-top: 7px;
}

.container {
    width: 100%;
}

.box {
    width: 993px;
    height: 484px;
    background: #174082;
    border-radius: 15px;
    box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.3);
}

.halfContainer {
    display: flex;
    flex-direction: column;
}

#red, #green {
    height: 484px;
}

#red {
    width: 60%;
}

#green {
    width: 40%;
    margin-left: -30px;
}

.day {
    font-size: 37.5px;
    color: #F0F1F5;
    margin-left: 70px;
    margin-top: 30px;
}

.date {
    font-size: 112.5px;
    color: #F0F1F5;
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
}

</style>
