<template>
    <div class="accmanagement">
        <div class="globalHeader">
            <h1>Accounts</h1>
        </div>
        <div class="container">
            <div class="boxHeader">
                <div class="boxHeaderTexts">
                    <p>#</p>
                    <p>Email</p>
                    <p>Role</p>
                    <p>Password</p>
                </div>
            </div>
            <div class="ticketBoxes">
                <div class="ticketBox" v-for="(item, index) in ticketCount" :key="index">
                    <p>{{ index + 1 }}</p>
                    <p>{{ item.service }}</p>
                    <p>{{ item.reference }}</p>
                    <div class="statusBox">
                        <button class="statusButton" :class="getStatusClass(item.status)"
                            @click.stop="toggleDropdown(index)">
                            {{ item.status }}
                        </button>
                        <div v-if="activeDropdown === index" class="dropdownMenu">
                            <p v-for="status in ['Pending', 'Done', 'In Progress', 'Rejected']" :key="status"
                                @click.stop="updateStatus(index, status)" :class="getStatusClass(status)">
                                {{ status }}
                            </p>
                        </div>
                    </div>
                </div>
            </div>
            <div class="boxHeader" @click="addAccountModal">
                <div class="boxHeaderTexts">
                    <p>+ Add New Account</p>
                </div>
            </div>
            <div v-if="blur" class="overlay" @click="closeModal"></div>
            <div v-if="showModal" class="modal-box" style="padding: 0">
                <div style="display: flex; flex-direction: column">
                    <div class="modalHeader" style="display: flex; padding: 1rem">
                        <span style="font-size: 1rem; font-weight: 600">Select Service</span>
                        <img :src="x" alt="x" style="margin-left: auto; cursor: pointer" @click="closeModal" />
                    </div>
                    <div style="height: 1px; width: 100%; background-color: #ced4da"></div>
                    <div class="modalBody" style="padding: 1rem">
                        <div class="input-group mb-3">
                            <input type="email" class="form-control" placeholder="Email Address"
                                aria-label="Email Address" aria-describedby="basic-addon1" v-model="email">
                        </div>
                        <div class="input-group mb-3">
                            <input type="text" class="form-control" placeholder="Role" aria-label="role"
                                aria-describedby="basic-addon1" v-model="role">
                        </div>
                        <div class="input-group mb-3">
                            <input type="password" class="form-control" placeholder="Password" aria-label="password"
                                aria-describedby="basic-addon1" v-model="password" style="background-color: #DEE2E6;">
                        </div>
                    </div>
                    <div style="height: 1px; width: 100%; background-color: #ced4da"></div>
                    <div class="modalFooter" style="display: flex; margin-left: auto; gap: 0.5rem; padding: 0 1rem 1rem 1rem;">
                        <button type="button" class="btn btn-secondary" @click="closeModal">
                            Cancel
                        </button>
                        <button type="button" class="btn btn-primary specbtn" style="border: none; background-color: #031633;"
                            @click="confirmAccount">
                            confirm
                        </button>
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import x from '@/assets/x-lg.svg'
export default {
    name: 'accmanagement',
    data() {
        return {
            x,
            ticketCount: [
                { service: "Driver's License Renewal", reference: "DL123", status: "Pending" },
                { service: "Student Permit Application", reference: "SP456", status: "Pending" },
                { service: "Conductor's License", reference: "CL789", status: "Pending" },
            ],
            activeDropdown: null,
            showModal: false,
            blur: false,
            email: "",
            role: "",
            password: "",
        };
    },
    methods: {
        toggleDropdown(index) {
            this.activeDropdown = this.activeDropdown === index ? null : index;
        },
        updateStatus(index, newStatus) {
            this.ticketCount[index].status = newStatus;
            this.activeDropdown = null;
        },
        getStatusClass(status) {
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
        addAccountModal() {
            this.showModal = true;
            this.blur = true;
        },
        closeModal() {
        this.showModal = false;
        this.blur = false;
        },
        confirmAccount() {
            this.showModal= false;
            this.blur = false;
        }
    },
};
</script>

<style scoped>
.accmanagement {
    background: #E9ECEF;
    height: 83vh;
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
    background: #031633;
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

.boxHeaderTexts p:nth-child(1),
.ticketBox p:nth-child(1) {
    flex: 1;
}

.boxHeaderTexts p:nth-child(2),
.ticketBox p:nth-child(2) {
    flex: 3;
    text-align: left;
}

.boxHeaderTexts p:nth-child(3),
.ticketBox p:nth-child(3) {
    flex: 2;
}

.boxHeaderTexts p:nth-child(4),
.ticketBox .statusBox {
    flex: 2;
    display: flex;
    align-items: center;
    justify-content: center;
}

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
    color: #198754;
}

.status-in-progress {
    color: #FFC107;
}

.status-pending {
    color: #ADB5BD;
}

.status-rejected {
    color: red;
}

.overlay {
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background: rgba(0, 0, 0, 0.5);
    backdrop-filter: blur(10px);
    z-index: 999;
}

.modal-box {
    position: fixed;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
    padding: 20px;
    background-color: white;
    border-radius: 10px;
    box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1);
    z-index: 1000;
    width: 38.9375rem;
    text-align: center;
}

.modal-box button {
    margin-top: 20px;
    padding: 10px 20px;
}
</style>
