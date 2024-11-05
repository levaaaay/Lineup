<template>
    <navbar />
    <land-page />
    <aboutUs />
    <qWithL />
    <lineupMinds />
    <foot />
</template>

<script>
import LandPage from '@/components/landPage.vue'
import qWithL from '@/components/qWithL.vue'
import navbar from '@/components/navbar.vue'
import AboutUs from '@/components/aboutUs.vue'
import lineupMinds from '@/components/lineupMinds.vue'
import foot from '@/components/footer.vue'

export default {
  components: { navbar, LandPage, AboutUs, qWithL, lineupMinds, foot},
}
</script>
