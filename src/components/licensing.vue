<template>
    <div class="licensing">
        <div class="globalHeader">
            <h1>Licensing</h1>
        </div>
        <div class="container">
            <div class="boxHeader">
                <div class="boxHeaderTexts">
                    <p>#</p>
                    <p>Service</p>
                    <p>Reference #</p>
                    <p>Status</p>
                </div>
            </div>
            <div class="ticketBoxes">
                <div class="ticketBox" v-for="(item, index) in ticketCount" :key="index">
                    <p>{{ index + 1 }}</p>
                    <p>{{ item.service }}</p>
                    <p>{{ item.reference }}</p>
                    <div class="statusBox">
                        <button
                            class="statusButton"
                            :class="getStatusClass(item.status)"
                            @click.stop="toggleDropdown(index)"
                        >
                            {{ item.status }}
                        </button>
                        <div v-if="activeDropdown === index" class="dropdownMenu">
                            <p
                                v-for="status in ['Pending', 'Done', 'In Progress', 'Rejected']"
                                :key="status"
                                @click.stop="updateStatus(index, status)"
                                :class="getStatusClass(status)"
                            >
                                {{ status }}
                            </p>
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
            ticketCount: [
                { service: "Driver's License Renewal", reference: "DL123", status: "Pending" },
                { service: "Student Permit Application", reference: "SP456", status: "Pending" },
                { service: "Conductor's License", reference: "CL789", status: "Pending" },
            ],
            activeDropdown: null, // Tracks which dropdown is active by index
        };
    },
    methods: {
        toggleDropdown(index) {
            // Toggle activeDropdown state
            this.activeDropdown = this.activeDropdown === index ? null : index;
        },
        updateStatus(index, newStatus) {
            this.ticketCount[index].status = newStatus;
            this.activeDropdown = null; // Close dropdown after selection
        },
        getStatusClass(status) {
            // Return a different class based on the status
            if (status === 'Done') {
                return 'status-done';
            } else if (status === 'In Progress') {
                return 'status-in-progress';
            } else if (status === 'Pending') {
                return 'status-pending';
            } else {
                return 'status-rejected';
            }
        },
    },
};
</script>

<style scoped>
.licensing {
    background: #E9ECEF;
}

.container {
    display: flex;
    flex-direction: column;
    align-items: center;
    padding: 3rem;
    gap: 0;
}

.boxHeader {
    width: 69rem;
    height: 3.0625rem;
    background: #052C65;
    display: flex;
}

.boxHeaderTexts {
    display: flex;
    justify-content: space-between;
    width: 100%;
}

.boxHeaderTexts p {
    color: white;
    font-weight: bold;
    margin: 0;
    flex: 1;
}

.boxHeaderTexts,
.ticketBox {
    display: flex;
    align-items: center;
    width: 100%;
    padding: 0 1rem;
}

.boxHeaderTexts p,
.ticketBox p {
    margin: 0;
    text-align: center;
    overflow: hidden;
    white-space: nowrap;
    text-overflow: ellipsis;
}

/* Assign consistent flex values for each column */
.boxHeaderTexts p:nth-child(1),
.ticketBox p:nth-child(1) {
    flex: 1;
    /* # column */
}

.boxHeaderTexts p:nth-child(2),
.ticketBox p:nth-child(2) {
    flex: 3;
    /* Service column */
    text-align: left;
    /* Align service name to the left */
}

.boxHeaderTexts p:nth-child(3),
.ticketBox p:nth-child(3) {
    flex: 2;
    /* Reference # column */
}

.boxHeaderTexts p:nth-child(4),
.ticketBox .statusBox {
    flex: 2;
    /* Handle/status column */
    display: flex;
    /* Ensure alignment of status box */
    align-items: center;
    /* Vertical alignment */
    justify-content: center;
    /* Center content */
}

/* Ensure consistent height for ticket rows */
.ticketBox {
    width: 69rem;
    height: 3rem;
    background: #ffffff;
    border-bottom: 1px solid #DEE2E6;
}

.statusBox {
    position: relative;
    overflow: visible;
    width: 13.125rem;
    height: 2rem;
    background-color: #EBE5FC;
    border-radius: 10px;
    display: flex;
    align-items: center;
    justify-content: center;
}

.statusButton {
    width: 100%;
    height: 100%;
    background: none;
    border: none;
    font-size: 1rem;
    cursor: pointer;
}

.dropdownMenu {
    position: absolute;
    top: 2.5rem;
    left: 0;
    background: white;
    box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
    border-radius: 5px;
    z-index: 10;
    width: 100%;
    display: flex;              
    flex-direction: column;      
    align-items: center;         
}

.dropdownMenu p {
    margin: 0;
    padding: 0.5rem 1rem;
    cursor: pointer;
    text-align: center;          
    display: block;              
}

.dropdownMenu p:hover {
    background: #f0f0f0;
}

.dropdownMenu p {
    margin: 0;
    padding: 0.5rem 1rem;
    cursor: pointer;
    text-align: center;  
    display: block;      
}

.dropdownMenu p:hover {
    background: #f0f0f0;
}


.status-done {
    color: green;
}

.status-in-progress {
    color: yellow;
}

.status-pending {
    color: gray;
}

.status-rejected {
    color: red;
}
</style>
