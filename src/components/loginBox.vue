<template>
    <div class="loginBox">
        <div class="box" >
            <div class="container">
            <img :src="ltoLogo" class="ltoLogo">
            </div>
            <div v-if="loginIsVisible">
                <div class="container">
                    <p>Sign in with Email</p>
                </div>
                <div class="container">
                    <form>
                        <input type="email" required placeholder="Email" class="email" v-model="email">
                        <input type="password" required placeholder="Password" class="password" v-model="password">
                    </form>
                </div>
                <div class="container">
                    <button class="button" @click="logIn" id="getStarted">Get Started</button>
                </div>
                <div class="container">
                    <div class="signIn">or sign in with</div>
                </div>
                <div class="container">
                    <img :src="googleLogo" class="googleLogo" @click="google">
                </div>
            </div>
            <div v-if="authIsVisible">
                <div class="container">
                    <div class="container">
                        <p>Enter the 6-digit code sent to your email.</p>
                    </div>
                    <div class="numContainer">
                        <div class="numbox" v-for="(digit, index) in code" :key="index">
                            <form>
                                <input type="text" required class="num" maxlength="1" inputmode="numeric" @input="validateInput($event)" v-model="code[index]">
                            </form>
                        </div>
                    </div>   
                    <button class="verifyButton" @click="authenticate">Verify</button>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import ltoLogo from "@/assets/ltoLogo.svg"
import googleLogo from "@/assets/googleLogo.svg"
import lock from "@/assets/lock.svg"

export default {
    name: "loginBox",
    data() {
        return {
            ltoLogo,
            googleLogo,
            lock,
            email: '',
            password: '',
            code: Array(6).fill(''),
            loginIsVisible: true,
            authIsVisible: false,
        }
    },
    methods: {
        logIn() {
            this.loginIsVisible = !this.loginIsVisible;
            this.authIsVisible = !this.authIsVisible;
        },
        google() {
            alert("tanginamo");
        },
        authenticate() {
            alert(this.code.join(''));
        },
        validateInput(event) {
            const input = event.target;
            if (!/^\d*$/.test(input.value)) {
                input.value = "";
            }
        },
    }
}
</script>

<style scoped>
.loginBox {
    display: flex;
    align-items: center;
    justify-content: center;
}

.box {
    width: 30%;
    height: 471px;
    background: linear-gradient(#B6CFF7, #F0F1F5);
    margin-top: 80px;
    border-radius: 15px;
    box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.3);
}

.ltoLogo {
    width: 119px;
    height: 119px;
    margin: 21px 0 0 0;
}

p {
    margin: 20px 0 18px 0;
    color: #212263;
    font-size: 20px;
}

.email, .password {
    width: 85%;
    height: 40px;
    box-sizing: border-box;
    border-radius: 10px;
    font-size: 16px;
    background-color: #F0F1F5;
    border: none;
    background-position: 10px center;
    background-repeat: no-repeat;
    margin-left: 32px;
    margin-bottom: 12px;
    padding-left: 35px;
}

.email {
    background-image: url('@/assets/emailLogo.svg');
}

.password {
    background-image: url('@/assets/lock.svg');
}

::placeholder {
    color: #BFC6D4;
    font-weight: 300;
}

.button {
    display: flex;
    justify-content: center;
    align-items: center;
    width: 85%;
    height: 46px;
    border-radius: 10px;
    background-color: #174082;
    font-size: 16px;
    color: #F0F1F5;
    font-weight: 600;
    border: none;
    cursor: pointer;
}

.verifyButton {
    display: flex;
    justify-content: center;
    align-items: center;
    width: 85%;
    height: 46px;
    border-radius: 10px;
    background-color: #174082;
    font-size: 16px;
    color: #F0F1F5;
    font-weight: 600;
    border: none;
    cursor: pointer;
}

#getStarted {
    margin-top: 20px;
}

.signIn {
    color: #212631;
    font-size: 15px;
    margin-top: 10px;
}

.googleLogo {
    margin: 5px 0 20px 0;
    cursor: pointer;
}

.numContainer {
    display: flex;
    justify-content: center;
    align-items: center;
    gap: 10px;
    margin-top: -45px;
    width: 100%
}

.num {
    width: 57px;
    height: 78px;
    box-sizing: border-box;
    border-radius: 20px;
    border: none;
    background-color: #F0F1F5;
    background-position: 10px center;
    background-repeat: no-repeat;
    padding-left: 22px;
    font-size: 30px;
}
</style>
