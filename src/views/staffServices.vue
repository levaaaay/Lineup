<template>
    <navbar />
    <StaffServicesInfo />
    <licensing />
    <registration />
    <letas />
    <foot />
</template>

<script>
import navbar from '@/components/staff/staffnavbar.vue'
import staffServicesInfo from '@/components/staff/staffServicesInfo.vue';
import licensing from '@/components/licensing.vue';
import registration from '@/components/registration.vue';
import letas from '@/components/letas.vue'
import foot from '@/components/staff/staffFooter.vue';

export default {
    components: { navbar, staffServicesInfo, licensing, registration, letas, foot },
};
</script>
