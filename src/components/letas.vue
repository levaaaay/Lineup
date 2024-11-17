<template>
    <div class="letas">
        <div class="globalHeader">
            <h1>Law Enforcement and Traffic Adjudication Service (LETAS)</h1>
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
    name: 'letas',
    data() {
        return {
            accordionId: `accordion-${Date.now()}`, 
            accordionItems: [
                { title: "Settlement of Apprehension Cases", content: "Details about Settlement of Apprehension Cases." },
                { title: "LETAS Fines and Penalties", content: "Details about LETAS Fines and Penalties." },
                { title: "Encoding of Alarm on Driver's License and Motor Vehicles in Relation to Orders Issued by Competent Courts or Quasi-Judicial Bodies", content: "Details about Encoding of Alarm on Driver's License and Motor Vehicles in Relation to Orders Issued by Competent Courts or Quasi-Judicial Bodies." },
            ],
        };
    },
}
</script>

<style scoped>
.letas {
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
