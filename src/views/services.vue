<template>
    <navbar />
    <servicesOffered />
    <specific-services />
    <foot />
</template>

<script>
import navbar from '@/components/navbar.vue'
import servicesOffered from '@/components/servicesOffered.vue';
import specificServices from '@/components/specificServices.vue';
import foot from '@/components/footer.vue'

export default {
    components: { navbar, servicesOffered, specificServices, foot},
}
</script>

