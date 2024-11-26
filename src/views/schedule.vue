<template>
    <div class="pageContainer">
        <navbar />
        <scheduleBox />
        <foot />
    </div>
</template>

<script>
import navbar from '@/components/navbar.vue';
import scheduleBox from '@/components/scheduleBox.vue';
import foot from '@/components/footer.vue';

export default {
    components: { navbar, scheduleBox, foot },
};
</script>

<style scoped>
body {
    margin: 0;
    overflow: hidden;
}

.pageContainer {
    display: flex;
    flex-direction: column;
    height: 100vh; 
}

.scheduleBox {
    flex: 1; 
    overflow: hidden; 
}

</style>
