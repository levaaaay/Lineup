<template>
    <navbar />
    <servicesInfo />
    <foot />
</template>

<script>
import navbar from '@/components/navbar.vue'
import servicesInfo from '@/components/servicesInfo.vue';
import foot from '@/components/footer.vue';

export default {
    components: { navbar, servicesInfo, foot},
}
</script>
