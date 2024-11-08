<template>
    <navbar />
    <scheduleBox />
</template>

<script>
import scheduleBox from '@/components/scheduleBox.vue';
import navbar from '@/components/navbar.vue';

export default {
    components: { scheduleBox, navbar }
}
</script>
