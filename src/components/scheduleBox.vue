<template>
    <div class="scheduleBox">
        <div class="globalHeader">
            <h1>Schedule</h1>
        </div>
        <div class="card-group">
            <div class="card mb-3" style="max-width: 44.7%;">
                <div class="row g-0">
                    <div class="col-md-6">
                        <div class="dateCardContent">
                            <div class="dateTime">
                                <h2 class="card-title">Sunday</h2>
                                <h2 class="card-title">11:47</h2>
                            </div>
                            <button class="btn btn-primary" type="submit">Queue now</button>
                        </div>
                    </div>
                    <div class="col-md-1">
                        <div class="line"></div>
                    </div>
                    <div class="col-md-5">
                        <div class="card-body">
                            <h5 class="card-title">Card title</h5>
                            <p class="card-text">This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.</p>
                            <p class="card-text"><small class="text-muted">Last updated 3 mins ago</small></p>
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
};
</script>

<style scoped>
.scheduleBox {
    background: #DEE2E6;
}

h1 {
    font-weight: 800 !important;
    padding-top: 2.43rem;
    padding-bottom: 1rem;
}

.card-group {
    justify-content: center;
    align-items: center;
}

.row {
    
    padding: 2rem 1.5rem 2rem 1.5rem;
}

.dateCardContent {
    display: flex;
    align-items: center;
    justify-content: space-between; 
    width: 90%;
    height: 50%;
    border: 1px solid #DEE2E6;
    border-radius: 1rem;
}

.dateTime {
    display: flex;
    flex-direction: column;
}

.card-title {
    margin: 0;
}


.col-md-2 {
    display: flex;
    justify-content: center;
    align-items: center;
}
.line {
    width: 1px;
    height: 100%;
    background: black;
}

</style>
