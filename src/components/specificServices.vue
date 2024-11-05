<template>
    <div class="specificServices">
        <div class="globalHeader">
            <p>Specific Service</p>
        </div>
    </div>
    <div class="centerWrap">
        <div class="container">
            <div v-for="(service, index) in services" :key="index" class="circleContainer">
                <div class="headerRow">
                    <div class="expand-icon" @click="toggleService(index)">
                        <span>{{ service.expanded ? '-' : '+' }}</span>
                    </div>
                    <div class="serviceHeader">
                        {{ service.title }}
                    </div>
                </div>
                <transition name="expand">
                    <div v-if="service.expanded" class="serviceDetails">
                        {{ service.details }}
                    </div>
                </transition>
            </div>
        </div>
    </div>
</template>

<script>
export default {
    name: 'specificServices',
    data() {
        return {
            services: [
                { title: 'Service 1', details: 'Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.', expanded: false},
                { title: 'Service 2', details: 'Details about Service 2', expanded: false},
                { title: 'Service 3', details: 'Details about Service 3', expanded: false},
                { title: 'Service 4', details: 'Details about Service 4', expanded: false},
                { title: 'Service 5', details: 'Details about Service 5', expanded: false},
                { title: 'Service 6', details: 'Details about Service 6', expanded: false},
                { title: 'Service 7', details: 'Details about Service 7', expanded: false},
                { title: 'Service 8', details: 'Details about Service 8', expanded: false},
            ]
        }
    },
    methods: {
       toggleService(index) {
        this.services[index].expanded = !this.services[index].expanded;
       }
    }
}
</script>

<style scoped>
.centerWrap {
    display: flex;
    justify-content: center;
    align-items: center;
}

.container {
    width: 1235px;
    height: 542px;
    overflow-y: auto;
    background: #E0E4EB;
    border-radius: 10px;
    padding: 20px 0px 35px 20px;
    box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.3);
    border: 1.5px solid black;
}

.container::-webkit-scrollbar {
  width: 20px; 
  scrollbar-color: black;
}

.container::-webkit-scrollbar-track {
  background: #dfe2e7; 
  border-radius: 8px;
}

.container::-webkit-scrollbar-thumb {
  background: #B6CFF7;
  border-radius: 8px;
}

.circleContainer {
    display: flex;
    flex-direction: column;
    margin-bottom: -20px;
    flex-shrink: 0;
    width: 100%;
}

.headerRow {
    display: flex;
    align-items: center;
}

.expand-icon {
    background: #f0f1f5;
    border-radius: 50%;
    width: 90px;
    height: 90px;
    display: flex;
    align-items: center;
    justify-content: center;
    font-weight: thin;
    font-size: 48px;
    z-index: 3; 
    margin-right: 20px;
}

.serviceHeader {
    background: #174082;
    color: #F0F1F5;
    border-radius: 15px;
    padding: 20px 55px;
    overflow: hidden;
    margin-left: -50px;
    margin-right: 30px;
    flex-grow: 1;
    z-index: 2;
}

.serviceDetails {
    background: #B6CFF7;
    padding: 10px;
    border-radius: 10px;
    color: #2F4F9E;
    margin-top: -50px;
    margin-left: 45px;
    margin-right: 27px;
    z-index: 1;
    padding-top: 50px;
}

.expand-enter-active, .expand-leave-active {
  transition: all 0s ease;
}

.expand-enter, .expand-leave-to /* .expand-leave-active in <2.1.8 */ {
  opacity: 0;
  height: 0;
}
</style>
