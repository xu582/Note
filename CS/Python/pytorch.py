import string

# 极其高端的pytorch
import torch
from torch import nn
from torch.utils.data import Dataset, DataLoader
from tqdm import trange

device = "cuda" if torch.cuda.is_available() else "cpu"
print(f"Using {device} device")


class NeuralNetwork(nn.Module):

    def __init__(self):
        super(NeuralNetwork, self).__init__()
        self.linear_stack = nn.Sequential(
            nn.Linear(26, 64),
            # 极其高端的激活函数
            nn.Hardsigmoid(),
            nn.Linear(64, 26),
            nn.Hardsigmoid(),
        )
        self.linear_stack_2 = nn.Sequential(
            nn.Linear(26, 64),
            nn.Hardsigmoid(),
            nn.Linear(64, 64),
            nn.Hardsigmoid(),
        )
        self.output_layer = nn.Linear(64, 26)

    def forward(self, x):
        y = self.linear_stack(x)
        # 极其高端的残差
        x = y + x
        y = self.linear_stack_2(x)
        y = self.output_layer(y)
        return y


model = NeuralNetwork().to(device)
x = torch.zeros((26, 26), dtype=torch.float32)
for i in range(26):
    x[i][i] = 1


class Data(Dataset):

    def __init__(self):
        self.data = list(zip(
            x,
            list(range(1, 26)) + [0],
        ))

    def __len__(self):
        return 26

    def __getitem__(self, idx):
        return self.data[idx]


data = Data()
dataloader = DataLoader(data, batch_size=1, shuffle=True)

loss_fn = nn.CrossEntropyLoss()
optimizer = torch.optim.Adam(model.parameters(), lr=1e-3)

for epoch in trange(500):
    for batch, (X, y) in enumerate(dataloader):
        X, y = X.to(device), y.to(device)
        pred = model(X)
        loss = loss_fn(pred, y)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

with torch.no_grad():
    pred = model(x)
    print(pred.argmax(1))

alphabet_digit_map = dict(zip(string.ascii_lowercase, x))
alphabet_digit_map_reverse = dict(zip(range(26), string.ascii_lowercase))


def trans_words(word):
    return "".join(alphabet_digit_map_reverse[model(
        alphabet_digit_map[w]).argmax().item()] for w in word)


my_word = "helloz"
print(trans_words(my_word))