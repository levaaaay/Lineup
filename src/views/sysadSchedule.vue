<template>
    <div class="pageContainer">
        <sysadSchedBox />
        <foot />
    </div>
</template>

<script>
import sysadSchedBox from '@/components/SysAd/adminSchedBox.vue';
import foot from '@/components/SysAd/adminfooter.vue';

export default {
    components: { sysadSchedBox, foot },
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
