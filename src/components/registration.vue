<template>
    <div class="registration">
        <div class="globalHeader">
            <h1>Registration</h1>
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
    name: 'registration',
    data() {
        return {
            accordionId: `accordion-${Date.now()}`, 
            accordionItems: [
                { title: "Sales Reporting and Registration of Motor Vehicles", content: "Details about Sales Reporting and Registration of Motor Vehicles." },
                { title: "Vehicle Encoding/Linking", content: "Details about Vehicle Encoding/Linking." },
                { title: "Renewal of Motor Vehicle (MV) Registration", content: "Details about Renewal of Motor Vehicle (MV) Registration." },
            ],
        };
    },
}
</script>

<style scoped>
.registration {
    background: #DEE2E6;
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
