<template>
    <navbar />
    <land-page />
    <aboutUs />
    <qWithL />
    <lineupMinds />
    <foot />
</template>

<script>
import LandPage from '@/components/staff/stafflandpage.vue'
import qWithL from '@/components/qWithL.vue'
import navbar from '@/components/staff/staffnavbar.vue'
import AboutUs from '@/components/aboutUs.vue'
import lineupMinds from '@/components/lineupMinds.vue'
import foot from '@/components/staff/staffFooter.vue'

export default {
  components: { navbar, LandPage, AboutUs, qWithL, lineupMinds, foot},
}
</script>
