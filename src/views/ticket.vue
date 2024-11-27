<template>
    <navbar />
    <ticketbody />
    <foot />
</template>

<script>
import navbar from '@/components/navbar.vue'
import foot from '@/components/footer.vue'
import ticketbody from '@/components/ticketbody.vue';

export default {
  components: { navbar, foot, ticketbody},
}
</script>
