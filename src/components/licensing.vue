<template>
    <div class="licensing">
        <div class="globalHeader">
            <h1>Licensing</h1>
        </div>
        <div class="container">
            <div class="accordion" :id="accordionId">
                <div class="accordion-item" v-for="(item, index) in accordionItems" :key="index">
                    <h2 class="accordion-header" :id="`heading-${accordionId}-${index}`">
                        <button
                            class="accordion-button"
                            type="button"
                            :data-bs-toggle="'collapse'"
                            :data-bs-target="`#collapse-${accordionId}-${index}`"
                            aria-expanded="true"
                            :aria-controls="`collapse-${accordionId}-${index}`"
                        >
                            {{ item.title }}
                        </button>
                    </h2>
                    <div
                        :id="`collapse-${accordionId}-${index}`"
                        class="accordion-collapse collapse"
                        :aria-labelledby="`heading-${accordionId}-${index}`"
                        :data-bs-parent="`#${accordionId}`"
                    >
                        <div class="accordion-body">
                            {{ item.content }}
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>


<script>
export default {
    name: 'licensing',
    data() {
        return {
            accordionId: `accordion-${Date.now()}`, // Unique ID for each component instance
            accordionItems: [
                { title: "Student-Driver's Permit", content: "Details about the Student-Driver's Permit." },
                { title: "New Driver's License (Non-Professional)", content: "Details about the Non-Professional License." },
                { title: "Conductor's License", content: "Details about the Conductor's License." },
            ],
        };
    },
};
</script>


<style scoped>
.licensing {
    background: #E9ECEF;
}

.centerWrap {
    display: flex;
    justify-content: center;
    align-items: center;
}

.container {
    display: flex;
    justify-content: center;
    align-items: center;
}

.accordion {
    width: 69rem;
    margin-bottom: 10rem;
}

button.accordion-button {
    background: #E7F1FF;
    border-bottom: 1px solid #DEE2E6;
    color: #0C63E4;
    --bs-primary-text-emphasis: #0C63E4;
}

.accordion-body {
    color: #68717A;
    margin: 1.5rem 1.5rem 1.5rem 1.5rem;
    border: 1px solid #DEE2E6;
    border-radius: 1rem;
    padding: 1.5rem 1.5rem 1.5rem 1.5rem;
}


</style>
