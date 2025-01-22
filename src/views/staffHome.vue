<template>
    <navbar />
    <land-page />
    <lineupMinds />
    <foot />
</template>

<script>
import LandPage from '@/components/staff/stafflandpage.vue'
import navbar from '@/components/staff/staffnavbar.vue'
import lineupMinds from '@/components/lineupMinds.vue'
import foot from '@/components/staff/staffFooter.vue'

export default {
  components: { navbar, LandPage, lineupMinds, foot},
}
</script>
