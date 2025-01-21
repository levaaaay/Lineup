<template>
    <div class="report">
        <div class="globalHeader">
            <h1>Report</h1>
        </div>
        <DraxlrEmbed id="6788f77686408a9d87f472ac" apiKey="ObpLA54jg7fFUnMcBZ8V3uYS7WXZi8" type="dashboardGroup"
            :options="options" :iframeStyle="{ width: '100%', height: '600px' }"
            @on-before-load="() => console.log('Loading...')" @on-after-load="() => console.log('Load complete')"
            @on-error="(error) => console.error('Error:', error)" />
    </div>
</template>

<script>
import DraxlrEmbed from "vue-draxlr-embed"
export default {
    name: "report",
    components: { DraxlrEmbed },
    data() {
        return {
            options: {
                "configuration": {
                    "hideHeader": false,
                    "showExport": true,
                    "showDrillDown": false,
                    "drillDownFields": {},
                    "backgroundColor": "#ffffff"
                },
                "filters": {}
            }
        }
    }
};
</script>

<style scoped>
.report {
    background: #DEE2E6;
    height: 47.5rem;
}
</style>
