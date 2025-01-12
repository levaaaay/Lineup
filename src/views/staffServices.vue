<template>
    <navbar />
    <staffSchedBox />
    <foot />
   
</template>

<script>
import staffSchedBox from '@/components/staff/staffSchedBox.vue';
import foot from '@/components/staff/staffFooter.vue';

export default {
    components: { staffSchedBox, foot },
};
</script>
